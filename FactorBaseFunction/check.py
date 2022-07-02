import pandas

def ts_sum(df, window=10):
    """Wrapper function to estimate rolling sum

    Args:
        df (pandas.DataFrame()): 
        window (int, optional): Defaults to 10.

    Returns:
        pandas.DataFrame(): _description_
    """
    return df.rolling(window).sum()

x = pandas.DataFrame([1,2,3,4,5,6])
print(ts_sum(x, 5))

