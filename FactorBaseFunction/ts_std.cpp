#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_std(
    const Rcpp::NumericVector& x,
    const int window,
    const int least = 0,
    const bool partial = false,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    if (partial)

    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        double mean = 0.0;
        for (int j = i; j > i - window; j--) {
            mean += ret[j];
        }
        for (int j = i; j > i - window; j)
    }
}
