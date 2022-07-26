import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def plot_nav(nav: pd.DataFrame, title: str, save_address: str):
    """
    画分组收益图, 若 save_address 为 '' 则不保存
    ---------
        nav数据结构
        --------------------------------------------------------
        |  time    | 1  | 2  | 3  | 4  | 5  | banchmark| Alpha |
        --------------------------------------------------------
        |2020-01-01|0.01|0.02|0.14|-0.2|0.08|   0.00   |  0.0  |
        --------------------------------------------------------
        |2020-01-02|0.11|-0.2|-0.1|0.33|0.10|   0.00   |  0.0  |
        --------------------------------------------------------
    """
    def to_drawdown_series(returns):
        """Convert returns series to drawdown series"""
        def compsum(returns):
            """Calculates rolling compounded returns"""
            return returns.add(1).cumprod() - 1

        def to_prices(returns, base=1e5):
            """Converts returns series to price data"""
            returns = returns.copy().fillna(0).replace(
                [np.inf, -np.inf], float('NaN'))

            return base + base * compsum(returns)

        def _prepare_prices(data, base=1.):
            """Converts return data into prices + cleanup"""
            data = data.copy()
            if isinstance(data, pd.DataFrame):
                for col in data.columns:
                    if data[col].dropna().min() <= 0 or data[col].dropna().max() < 1:
                        data[col] = to_prices(data[col], base)

            # is it returns?
            # elif data.min() < 0 and data.max() < 1:
            elif data.min() < 0 or data.max() < 1:
                data = to_prices(data, base)

            if isinstance(data, (pd.DataFrame, pd.Series)):
                data = data.fillna(0).replace(
                    [np.inf, -np.inf], float('NaN'))

            return data

        prices = _prepare_prices(returns)
        dd = prices / np.maximum.accumulate(prices) - 1.
        return dd.replace([np.inf, -np.inf, -0], 0)

    plt.rcParams["font.family"] = "Arial"
    
    style_pool = [['Navy', '-'], ['#348dc1', '-'], ['DimGray', '-'], ['DarkKhaki', '-'], ['LightSteelBlue', '-']]
    _, ax0 = plt.subplots(figsize=(12, 4), facecolor='white')
    drardown = to_drawdown_series(nav["Alpha"])
    ax0.plot(drardown, color="LightGrey", lw=1, alpha=0.4)
    ax0.fill_between(drardown.index, 0, drardown, color="LightGrey", alpha=0.2)
    ax0.set_ylabel("Drawdown", fontweight='bold', fontsize=10)
    ax0.grid(b=True, axis='x')
    ax0.tick_params(labelsize=10)
    ax=ax0.twinx()
    ax.set_ylabel("Cumulative Reture", fontweight='bold', fontsize=10)
    groups = [i for i in nav.columns.tolist() if i not in ['benchmark', 'Alpha']]
    # 设置标题
    plt.title(title, fontweight='bold', fontsize=10)
    for g in range(len(groups)):
        if 0 <= g <= 4:
            ax.plot(nav['G' + str(g + 1)], lw=1, color=style_pool[g][0], ls=style_pool[g][1], label=F'G{g + 1}')
        else:
            ax.plot(nav['G' + str(g + 1)], lw=1, label=F'G{g + 1}')
    ax.plot(nav['benchmark'], lw=1, color='black', ls='-', label='benchmark')
    ax.plot(nav['Alpha'], lw=1, color='#C00000', ls='--', label='Alpha', alpha=0.7)
    ax.axhline(1, color='black', lw=0.5)
    ax.grid()
    ax.legend(fontsize=8)
    ax.tick_params(labelsize=10)
    
    if save_address != '':
        plt.savefig(save_address, dpi=300)
    plt.show()