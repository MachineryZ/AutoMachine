# Rcpp 

Rcpp 是在 R 环境中可以运行的 cpp 包

在 cpp 源文件中备注 Rcpp::export 即可嵌入目标代码块

在 R 环境中运行：
~~~R
library("Rcpp")
sourceCpp(file="your_file_name.cpp")
~~~
即可运行
