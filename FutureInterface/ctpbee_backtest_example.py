from datetime import datetime
from ctpbee import get_current_trade_day, CtpBee
from ctpbee import CtpbeeApi
from ctpbee.constant import TickData, OrderData, Offset, Direction, TradeData, Status, ContractData, BarData
from ctpbee.message import Mail

import pandas as pd

CODE = "rb2105.SHFE"


class Str(CtpbeeApi):
    def __init__(self):
        super().__init__("api")
        self.instrument_set = [CODE]

    def on_bar(self, tick: BarData) -> None:
        print(tick.close_price)

    def on_init(self, init: bool):
        print("新的一天开始了")


def run_looper_app():
    info = {
        "PATTERN": "looper",
        "LOOPER": {
            "initial_capital": 10000,  # 初始资金 
            "deal_pattern": "price",  # 撮合模式 
            "margin_ratio": {
                CODE: 0.1,  # 保证金占用率 
            },
            "commission_ratio": {
                CODE: {
                    "close": 0.00003,  # 平昨手续费 <支持整数位手续费，比如三块 >
                    "close_today": 0.00003  # 平今手续费 
                },
            },
            "size_map": {
                CODE: 10  # 合约乘数 
            }
        }
    }
    app = CtpBee("looper", __name__)
    app.config.from_mapping(info)
    strategy = Str()
    data = pd.read_csv("rbdata.csv")  # 读取k线的csv
    data = list(data.to_dict(orient="index").values())
    for x in data:
        x["datetime"] = datetime.strptime(x["datetime"], "%Y-%m-%d %H:%M:%S")  # 转换时间为标准datetime格式
    app.add_data(data)  # 加载进去
    app.add_extension(strategy)
    app.start()
    result, trade = app.get_result(report=True, auto_open=True)
    print(result)


if __name__ == '__main__':
    run_looper_app()