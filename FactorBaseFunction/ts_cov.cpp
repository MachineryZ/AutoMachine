#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_cov(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const int window,
    const bool partial = false,
    const bool least = 1,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    int y_size = y.size();
    if (x_size != y.size())
        throw std::range_error("two input vector should be in the same dimension")
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    

}

