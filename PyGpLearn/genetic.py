import itertools
from abc import ABCMeta, abstractmethod
from time import time
from warnings import warn

import numpy as np
import pandas
from joblib import Parallel, delayed
from scipy.stats import rankdata
from sklearn.base import BaseEstimator
from typing import List, Tuple, Set

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
    
    def _verbose_reporter(self, run_details=None):
        """
        A report of the progress of the evolution process
        Parameters:
        run_details: dict
            information about the evolution

        
        """

if __name__ == '__main__':
    pass