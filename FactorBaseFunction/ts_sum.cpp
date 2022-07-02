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
    
    for (int i = window - 1; i < x_size; i++) {
        ret[i] = 0.0;
        for (int j = i; j > i - window; j--) {
            if (sign == 0)  ret[i] += x[j];
            else if (sign == -1 and x[j] < 0)   ret[i] += x[j];
            else if (sign == 1 and x[j] > 0)    ret[i] += x[j];
        }
    }
    if (partial == true) {
        for (int i = window - least; i < window - 1; i++) {
            ret[i] = 0.0;
            for (int j = i; j >= i - least + 1; j--) {
                if (sign == 0)  ret[i] += x[j];
                else if (sign == -1 and x[j] < 0)   ret[i] += x[j];
                else if (sign == 1 and x[j] > 0)    ret[i] += x[j];
            }
        }
    }
    return ret;
}