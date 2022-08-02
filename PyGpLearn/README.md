# Genetic Programming in python version

在同目录下，我们已经获取了一个知乎上愿意分享的网友写的一个 naive_py_gplearn 的代码，从代码中我们可以看到一个 gplearn 的流程应该是：
1. 定义好函数，比如 ts_sum 等
2. 将定义好的函数通过 make_function 得到 Function 类的实例
3. 定义好 metric，比如 ic 是目标函数
4. 定义好 SymbolicTransformer 是 gp 的算法实例，也包括超参数等
5. 调用 SymbolicTransformer 的 fit 函数，开始迭代
6. 得到最后的迭代结果

