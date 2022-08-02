"""The underlying data structure used in gplearn.
The :mod:`gplearn._program` module contains the underlying representation of a
computer program. It is used for creating and evolving programs used in the
:mod:`gplearn.genetic` module.
"""

import numpy as np
from sklearn.utils.random import sample_without_replacement