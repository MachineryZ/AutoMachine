import itertools
from abc import ABCMeta, abstractmethod
from time import time
from warnings import warn

import numpy as np
import pandas
from joblib import Parallel, delayed
from scipy.stats import rankdata
from sklearn.base import BaseEstimator
from sklearn.utils import compute_sample_weight
from sklearn.utils.validation import check_array, _check_sample_weight
from sklearn.utils.multiclass import check_classification_targets
from typing import List, Tuple, Set, Dict
from utils import check_random_state
from utils import _partition_estimators


MAX_INT = np.iinfo(np.int32).max

class BaseSymbolic(BaseEstimator, mataclass=ABCMeta):
    """
    Base class for SymbolicRegression / Classification Estimators

    This class should not be used directly
    Use derived classes instead
    """
    @abstractmethod
    def __init__(self,
        *,
        population_size: int = 1000,
        hall_of_fame: int = None,
        n_components: int = None,
        generations: int = 20,
        tournament_size: int = 20,
        stopping_criteria: float = 0.0,
        const_range: Tuple[float] = (-1., 1.),
        init_depth: Tuple[int] = (2, 6),
        init_method: str = 'half and half',
        function_set: Set[str] = ('add', 'sub', 'mul', 'div'),
        transformer=None,
        metric: str = 'mean absolute error',
        parsimony_coefficient: float = 0.001,
        p_crossover: float = 0.9,
        p_subtree_mutation: float = 0.01,
        p_hoist_mutation: float = 0.01,
        p_point_mutation: float = 0.01,
        p_point_replace: float = 0.05,
        max_samples: float = 1.0,
        class_weight=None,
        feature_names=None,
        warm_start=False,
        low_memory=False,
        n_jobs=1,
        verbose=0,
        random_state=None
    ):
        self.population_size = population_size
        self.hall_of_fame = hall_of_fame
        self.n_components = n_components
        self.generations = generations
        self.tournament_size = tournament_size
        self.stopping_criteria = stopping_criteria
        self.const_range = const_range
        self.init_depth = init_depth
        self.init_method = init_method
        self.function_set = function_set
        self.transformer = transformer
        self.metric = metric
        self.parsimony_coefficient = parsimony_coefficient
        self.p_crossover = p_crossover
        self.p_subtree_mutation = p_subtree_mutation
        self.p_hoist_mutation = p_hoist_mutation
        self.p_point_mutation = p_point_mutation
        self.p_point_replace = p_point_replace
        self.max_samples = max_samples
        self.class_weight = class_weight
        self.feature_names = feature_names
        self.warm_start = warm_start
        self.low_memory = low_memory
        self.n_jobs = n_jobs
        self.verbose = verbose
        self.random_state = random_state
    
    def _verbose_reporter(self, run_details: Dict = None):
        """
        A report of the progress of the evolution process
        Parameters:
        run_details: dict
            information about the evolution
        """
        if run_details is None:
            print('    |{:^25}|{:^42}|'.format('Population Average',
                                               'Best Individual'))
            print('-' * 4 + ' ' + '-' * 25 + ' ' + '-' * 42 + ' ' + '-' * 10)
            line_format = '{:>4} {:>8} {:>16} {:>8} {:>16} {:>16} {:>10}'
            print(line_format.format('Gen', 'Length', 'Fitness', 'Length',
                                     'Fitness', 'OOB Fitness', 'Time Left'))
        else:
            # Estimate remaining time for run
            gen = run_details['generation'][-1]
            generation_time = run_details['generation_time'][-1]
            remaining_time = (self.generations - gen - 1) * generation_time
            if remaining_time > 60:
                remaining_time = '{0:.2f}m'.format(remaining_time / 60.0)
            else:
                remaining_time = '{0:.2f}s'.format(remaining_time)

            oob_fitness = 'N/A'
            line_format = '{:4d} {:8.2f} {:16g} {:8d} {:16g} {:>16} {:>10}'
            if self.max_samples < 1.0:
                oob_fitness = run_details['best_oob_fitness'][-1]
                line_format = '{:4d} {:8.2f} {:16g} {:8d} {:16g} {:16g} {:>10}'

            print(line_format.format(run_details['generation'][-1],
                                     run_details['average_length'][-1],
                                     run_details['average_fitness'][-1],
                                     run_details['best_length'][-1],
                                     run_details['best_fitness'][-1],
                                     oob_fitness,
                                     remaining_time))

    def fit(self, X, y, sample_weight=None):
        """Fit the Genetic Program according to X, y.
        Parameters
        ----------
        X : array-like, shape = [n_samples, n_features]
            Training vectors, where n_samples is the number of samples and
            n_features is the number of features.
        y : array-like, shape = [n_samples]
            Target values.
        sample_weight : array-like, shape = [n_samples], optional
            Weights applied to individual samples.
        Returns
        -------
        self : object
            Returns self.
        """


if __name__ == '__main__':
    pass