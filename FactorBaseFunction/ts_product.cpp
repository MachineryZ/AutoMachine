#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_product(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 1,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        ret[i] = 1.0;
        for (int j = i; j > i - window; j--) {
            ret[i] *= x[j];
        }
    }

    if (partial == true) {
        for (int i = least - 1; i < window - 1; i++) {
            ret[i] = 1.0;
            for (int j = i; j >= 0; j--) {
                ret[i] *= x[j];
            }
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp("ts_product.cpp")
// print(ts_product(c(1,2,3,4,5), 3))
