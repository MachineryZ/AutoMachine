from optparse import Option
import pandas
import numpy as np
from typing import Union

def ts_sum(
    x: Union[pandas.DataFrame, np.ndarray] = None,
    window: int = None,
    partial: bool = None,
    min_periods: int = None,
    center: bool = False,
):
    """Wrapper function to estimate SMA(simplest moving average)
    Also can be renamed as ts_mean function, which means rolling mean

    Args:
        df (pandas.DataFrame):
        window (int, optional): Defaults to 10.

    Returns:
        pandas.DataFrame: 
    """
    if isinstance(x, pandas.DataFrame):
        if partial is True:
            return x.rolling(window=window, min_periods=min_periods, center=center).sum()
        elif partial is False:
            return x.rolling(window=window, min_periods=None, center=center).sum()

