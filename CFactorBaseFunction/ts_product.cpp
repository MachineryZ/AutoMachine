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
    double product_x = 1.0;

    for (int i = 0; i < x_size; i++) {
        product_x *= x[i];
        
        if (i >= window) {
            product_x /= x[i - window];
        }
        if (i >= window - 1) {
            ret[i] = product_x;
        }
        else if (partial == true and i >= least - 1) {
            ret[i] = product_x;
        }

    }
    return ret;
}
// library("Rcpp")
// sourceCpp("ts_product.cpp")
// print(ts_product(c(1,2,3,4,5), 3))
