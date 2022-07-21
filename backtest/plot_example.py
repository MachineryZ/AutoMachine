import pandas as pd
import matplotlib.pyplot as plt

def plot_nav(nav: pd.DataFrame, title: str, save_address: str):
    """
    画分组收益图, 若 save_address 为 '' 则不保存
    ---------
        nav数据结构
        --------------------------------------------------------
        |  time    | 1  | 2  | 3  | 4  | 5  | bancnmark| Alpha |
        --------------------------------------------------------
        |2020-01-01|0.01|0.02|0.14|-0.2|0.08|    xxx   |  xxx  |
        --------------------------------------------------------
        |2020-01-02|0.11|-0.2|-0.1|0.33|0.10|    xxx   |  xxx  |
        --------------------------------------------------------
    """
    plt.rcParams['font.family'] = 'serif'
    style_pool = [['Navy', '-'], ['LightGrey', '-.'], ['DimGray', '-.'], ['DarkKhaki', '-.'], ['LightSteelBlue', '-']]

    _, ax = plt.subplots(figsize=(18, 6), facecolor='white')
    groups = [i for i in nav.columns.tolist() if i not in ['benchmark', 'Alpha']]
    
    plt.title(title)
    
    for g in range(len(groups)):
        if 0 <= g <= 4:
            ax.plot(nav['G' + str(g + 1)], color=style_pool[g][0], ls=style_pool[g][1], label=F'G{g + 1}')
        else:
            ax.plot(nav['G' + str(g + 1)], label=F'G{g + 1}')
    
    ax.plot(nav['benchmark'], color='black', ls='-', label='benchmark')
    ax.plot(nav['Alpha'], color='r', ls='--', label='Alpha')
    ax.axhline(1, color='black', lw=0.5)
    ax.legend()
    if save_address != '':
        plt.savefig(save_address, dpi=300)
    plt.show()
