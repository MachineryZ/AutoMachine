import ctpbee

# ctpBee 的核心模块
app = ctpbee.CtpBee("somewheve", __name__)

# 配置模块
# 每个核心 APP 都有一份 config，是字典格式的配置
# json support
# app.config.from_json(json_path)

# mapping support
# app.config.from_mapping(mapping_obj)

# pyfile support
# app.config.from_pyfile(pyfile_path)

# obj support
# app.config.from_object(obj)


# 策略模块
# 实例化一个叫 data_recorder 的策略，名字就叫 data_recorder
data_recorder = ctpbee.CtpbeeApi("data_recorder")

@data_recorder.route(handler="tick")
def handler_tick(self, tick):
    print(tick)

@data_recorder.route(handler="bar")
def handler_bar(self, bar):
    print(bar)

# 然后把他载入到app中
app.add_extension(data_recorder)

# 那么当行情tick到来的时候会自动触发handler_tick里面的代码，bar/k线也是同样的道理 但是只有这两种API吗，
# 不, 远不如此，route里面的handler 还可以接受更多的参数，不过他们是非必须，按照你们的意见进行编写即可， 包括以下:

# contract 合约
# position 持仓
# trade 成交
# order 报单
# init 初始化
# shared 分时图 / todo: 后面进行移除
# timer 定时器，一秒触发一次

@data_recorder.route(handler="bar")
def handler_bar(self, bar):
    # 调用注册的事件
    self.get_position_by_ld(bar.local_symbol, bar.direction)
    print(bar)


@data_recorder.register()
def get_position_by_ld(self, local_symbol, direction):
    """ 根据local_symbol和direction获取持仓 """
    print("I AM A METHOD")


if __name__ == '__main__':
    app = ctpbee.CtpBee("demo", __name__)
    info = {}
    app.config.from_mapping(info)
    app.add_extension(data_recorder)
    app.start()