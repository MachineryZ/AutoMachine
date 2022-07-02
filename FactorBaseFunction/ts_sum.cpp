#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const Rcpp::NumericVector weight = NULL,
    const bool partial = false,
    const int least = 0,
    const float intercept = 0.0,
    const int sign = 0,
    const int last = 0,
    const int skip = 1,
    const double fill = NA_REAL
) {
    // Args:
    //      x: input vector, 
    //      window: rolling window size, int 
    //      weight: whether use weighted rolling type
    //      partial: if true, use partial; if false, fill NA
    //      least: shortest window for ts_sum
    //      intercept: bias, default 0
    //      sign: if 0, add all number; if 1, only add positive;
    //          if -1, only add negative
    //      last: last 
    //      skip: how to rolling add, skip means stride
    //      fill: how to fill nan, default NA_REAL
    // Returns:
    //      ret: the ts_sum result
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer")
    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        ret[i] = 0.0;
        for (int j = i; j > i - window; j--) {
            ret[i] += x[j];
        }
    }
    if (partial == true) {
        ret[i] = 0.0;
        for (it i = least - 1; i < window - 1; i++) {
            ret[i] += x[j];
        }
    }
    return ret;
}


library("Rcpp")
sourceCpp(code='
#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const Rcpp::NumericVector weight = NULL,
    const bool partial = false,
    const int least = 0,
    const float intercept = 0.0,
    const int sign = 0,
    const int last = 0,
    const int skip = 1,
    const double fill = NA_REAL
) {
    // Args:
    //      x: input vector, 
    //      window: rolling window size, int 
    //      weight: whether use weighted rolling type
    //      partial: if true, use partial; if false, fill NA
    //      least: shortest window for ts_sum
    //      intercept: bias, default 0
    //      sign: if 0, add all number; if 1, only add positive;
    //          if -1, only add negative
    //      last: last 
    //      skip: how to rolling add, skip means stride
    //      fill: how to fill nan, default NA_REAL
    // Returns:
    //      ret: the ts_sum result
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer")
    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        ret[i] = 0.0;
        for (int j = i; j > i - window; j--) {
            ret[i] += x[j];
        }
    }
    if (partial == true) {
        ret[i] = 0.0;
        for (it i = least - 1; i < window - 1; i++) {
            ret[i] += x[j];
        }
    }
    return ret;
}


')
print(ts_sum(1:5, 3))

(x, window, weight, intercept = TRUE, sign= 0L, skip =0L, partial =FALSE, 
 least = 3L, fill= NA_real_, threads= 1L, last= 0L)

window：窗大小
partial：是否使用least这个
least：最小窗大小相加
weight：数组
intercept：截距
last：
sign：如果是 0 就是都统计，1就是只统计正数，-1就是只统计负的
last：最后N个数的值
