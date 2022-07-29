#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const Rcpp::NumericVector weight,
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
        throw std::range_error("window must be a positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);
    
    double sum = 0.0;
    for (int i = 0; i < x_size; i++) {
        sum += x[i];
        if (i > window - 1)
            sum -= x[i - window];
        if ((partial == true and i >= least - 1) or i >= window - 1)
            ret[i] = sum;
    }
    return ret;
}

// library("Rcpp")
// sourceCpp(file="ts_sum.cpp")
// print(ts_sum(1:5, 3, 1:1, least=2, partial=TRUE))