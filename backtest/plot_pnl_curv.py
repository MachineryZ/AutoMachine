import pandas
import numpy as np
import torch
import matplotlib.pyplot as plt

def plot_pnl_curv(
    x: pandas.DataFrame,
    title: str,
    save_path: str
):
    _, ax0 = plt.subplots(figsize=(12, 4), facecolor="white")

    # color: 
    # 
    # ls: linestyle, '-', '--', ':'
    # label: curve label name, str
    # alpha: transparent, float 0~1
    ax0.plot(x, lw=1, color="red", ls='-', label="Alpha", alpha=1.0)
    ax0.legend(fontsize=8)
    plt.title(title)
    plt.savefig(save_path)

    _, ax1 = plt.subplots(figsize=(12, 4), facecolor="white")

    # color: 
    # lw: linewidth, int
    # ls: linestyle, '-', '--', ':'
    # label: curve label name, str
    # alpha: transparent, float 0~1
    x2 = np.random.randn(1000)
    ax1.plot(x, lw=1, color="red", ls='-', label="Alpha", alpha=1.0)
    # ax1.plot(x2, lw=1, color="green", ls='-', label="fuck you", alpha=1.0)
    x_max = x.max()
    x_min = x.min()
    for i in range(int(x_min), int(x_max) + 1, 50):
        ax1.axhline(i, color="black", lw=0.5)
    
    # fill_between: to draw drawdown
    # position = []
    # pre = 0.0
    # for i in range(len(x) - 1):
    #     if 

    ax1.grid()
    ax1.legend()
    # ax1.set_xticks(range(1,1000))
    x_ticks = range(0, 1000, 100)
    x_dates = range(0, 1000, 100)
    dd = x / np.maximum.accumulate(x) - 1.
    plt.xticks(x_ticks, x_dates)
    ax1.plot(dd, lw=1, color="black", ls="-", label="dd", alpha=1.0)
    ax1.fill_between(dd, 0, dd, color="LightGrey", alpha=0.7)
    plt.title(title)
    plt.savefig("./another.jpg")

if __name__ == "__main__":
    # x = pandas.DataFrame(np.random.randn(1000))
    x = np.random.randn(1000) + np.array(range(0, 1000))/5
    plot_pnl_curv(x=x, title="example", save_path="./example.jpg")
