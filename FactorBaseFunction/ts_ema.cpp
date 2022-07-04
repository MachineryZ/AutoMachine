#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp:: NumericVector ts_ema(
    const Rcpp::NumericVector& x,
    const int window,
    const double beta,
    const bool partial = false,
    const int least = 0,
    const int sign = 0,
    const int stride = 1,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        ret[i] = 0.0;
        for (int j = i - window + 1; j <= i; j++) {
            ret[i] *= beta;
            if (sign == 0)    ret[i] += x[j];
            else if (sign == -1 and x[j] < 0)    ret[i] += x[j];
            else if (sign == 1 and x[j] > 0)    ret[i] += x[j];
        }
    }
    if (partial == true) {
        for (int i = window - least; i < window - 1; i++) {
            ret[i] = 0.0;
            for (int j = i - least + 1; j <= i; j++) {
                ret[i] *= beta;
                if(sign == 0)    ret[i] += x[j];
                else if(sign == -1 and x[j] < 0)    ret[i] += x[j];
                else if(sign == 1 and x[j] > 0)    ret[i] += x[j];
            }
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_ema.cpp")
// print(ts_ema(1:5, 3, 0.5))

