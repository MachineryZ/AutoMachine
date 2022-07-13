#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp:: NumericVector ts_ema(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    // ema(t) = price(t) * alpha + ema(t-1) * (1 - alpha)

    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);
    double ema = 0.0;

    for (int i = 0; i < x_size; i++) {
        double alpha = i >= window - 1 ? (2 / (window + 1)) : (2 / (i + 1));
        ema = x[i] * alpha + ema * (1 - alpha);
        if ((partial == true and i >= least - 1) or (i >= window - 1)) {
            ret[i] = ema;
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_ema.cpp")
// print(ts_ema(1:5, 3))

