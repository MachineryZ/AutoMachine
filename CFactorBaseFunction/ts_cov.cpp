#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_cov(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const int window,
    const bool partial = false,
    const int least = 1,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    int y_size = y.size();
    if (x_size != y.size())
        throw std::range_error("two input vector should be in the same dimension");
    if (x_size == 0)
        return x;
    if (window <= 1)
        throw std::range_error("window must be a greater than 1 positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);

    double sum_x = 0.0;
    double sum_y = 0.0;
    double cross_xy = 0.0;

    for (int i = 0; i < x_size; i++) {
        sum_x += x[i];
        sum_y += y[i];
        cross_xy += x[i] * y[i];
        if (partial == true and i >= least - 1) {
            ret[i] = cross_xy / i - sum_x * sum_y / (i + 1) / i;
        }
        else if (i >= window - 1) {
            if (i >= window) {
                sum_x -= x[i - window];
                sum_y -= y[i - window];
                cross_xy -= x[i - window] * y[i - window];
            }
            ret[i] = cross_xy / (window - 1) - sum_x / window * sum_y / (window - 1);
        }
    }
    return ret;
}

// library("Rcpp")
// sourceCpp(file="ts_cov.cpp")
// print(ts_cov(c(1,2,3,5,4), c(5,4,3,2,1), 3))