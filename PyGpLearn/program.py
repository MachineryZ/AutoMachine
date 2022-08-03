"""The underlying data structure used in gplearn.
The :mod:`gplearn._program` module contains the underlying representation of a
computer program. It is used for creating and evolving programs used in the
:mod:`gplearn.genetic` module.
"""

import numpy as np
from sklearn.utils.random import sample_without_replacement

from functions import _Function
from utils import check_random_state

class _Program(object):
    """A program-like representation of the evolved program.
    This is the underlying data-structure used by the public classes in the
    :mod:`gplearn.genetic` module. It should not be used directly by the user.
    Parameters
    ----------
    function_set : list
        A list of valid functions to use in the program.
    arities : dict
        A dictionary of the form `{arity: [functions]}`. The arity is the
        number of arguments that the function takes, the functions must match
        those in the `function_set` parameter.
    init_depth : tuple of two ints
        The range of tree depths for the initial population of naive formulas.
        Individual trees will randomly choose a maximum depth from this range.
        When combined with `init_method='half and half'` this yields the well-
        known 'ramped half and half' initialization method.
    init_method : str
        - 'grow' : Nodes are chosen at random from both functions and
          terminals, allowing for smaller trees than `init_depth` allows. Tends
          to grow asymmetrical trees.
        - 'full' : Functions are chosen until the `init_depth` is reached, and
          then terminals are selected. Tends to grow 'bushy' trees.
        - 'half and half' : Trees are grown through a 50/50 mix of 'full' and
          'grow', making for a mix of tree shapes in the initial population.
    n_features : int
        The number of features in `X`.
    const_range : tuple of two floats
        The range of constants to include in the formulas.
    metric : _Fitness object
        The raw fitness metric.
    p_point_replace : float
        The probability that any given node will be mutated during point
        mutation.
    parsimony_coefficient : float
        This constant penalizes large programs by adjusting their fitness to
        be less favorable for selection. Larger values penalize the program
        more which can control the phenomenon known as 'bloat'. Bloat is when
        evolution is increasing the size of programs without a significant
        increase in fitness, which is costly for computation time and makes for
        a less understandable final result. This parameter may need to be tuned
        over successive runs.
    random_state : RandomState instance
        The random number generator. Note that ints, or None are not allowed.
        The reason for this being passed is that during parallel evolution the
        same program object may be accessed by multiple parallel processes.
    transformer : _Function object, optional (default=None)
        The function to transform the output of the program to probabilities,
        only used for the SymbolicClassifier.
    feature_names : list, optional (default=None)
        Optional list of feature names, used purely for representations in
        the `print` operation or `export_graphviz`. If None, then X0, X1, etc
        will be used for representations.
    program : list, optional (default=None)
        The flattened tree representation of the program. If None, a new naive
        random tree will be grown. If provided, it will be validated.
    Attributes
    ----------
    program : list
        The flattened tree representation of the program.
    raw_fitness_ : float
        The raw fitness of the individual program.
    fitness_ : float
        The penalized fitness of the individual program.
    oob_fitness_ : float
        The out-of-bag raw fitness of the individual program for the held-out
        samples. Only present when sub-sampling was used in the estimator by
        specifying `max_samples` < 1.0.
    parents : dict, or None
        If None, this is a naive random program from the initial population.
        Otherwise it includes meta-data about the program's parent(s) as well
        as the genetic operations performed to yield the current program. This
        is set outside this class by the controlling evolution loops.
    depth_ : int
        The maximum depth of the program tree.
    length_ : int
        The number of functions and terminals in the program.
    """
    def __init__(self,
                 function_set,
                 arities,
                 init_depth,
                 init_method,
                 n_features,
                 const_range,
                 metric,
                 p_point_replace,
                 parsimony_coefficient,
                 random_state,
                 transformer=None,
                 feature_names=None,
                 program=None):

        self.function_set = function_set
        self.arities = arities
        self.init_depth = (init_depth[0], init_depth[1] + 1)
        self.init_method = init_method
        self.n_features = n_features
        self.const_range = const_range
        self.metric = metric
        self.p_point_replace = p_point_replace
        self.parsimony_coefficient = parsimony_coefficient
        self.transformer = transformer
        self.feature_names = feature_names
        self.program = program

        if self.program is not None:
            if not self.validate_program():
                raise ValueError('The supplied program is incomplete.')
        else:
            # Create a naive random program
            self.program = self.build_program(random_state)

        self.raw_fitness_ = None
        self.fitness_ = None
        self.parents = None
        self._n_samples = None
        self._max_samples = None
        self._indices_state = None

    def build_program(self, random_state):
        """Build a naive random program.
        Parameters
        ----------
        random_state : RandomState instance
            The random number generator.
        Returns
        -------
        program : list
            The flattened tree representation of the program.
        """

        if self.init_method == "half and half":
            method = ("full" if random_state.randint(2) else "grow")
        else:
            method = self.init_method
        max_depth = random_state.randint(*self.init_depth)
    
    