#include <Rcpp.h>
#include <cmath>

//[[Rcpp::export]]
Rcpp::NumericVector ts_std(
    const Rcpp::NumericVector& x,
    const int window,
    const int least = 2,
    const bool partial = false,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");        

    Rcpp::NumericVector ret(x_size, fill);

    double sum_x = 0.0;
    double square_sum_x = 0.0;

    for (int i = 0; i < x_size; i++) {
        sum_x += x[i];
        square_sum_x += x[i] * x[i];
        if (i > window - 1) {
            sum_x -= x[i];
            square_sum_x -= x[i] * x[i];
        }
        if (i >= window - 1) {
            ret[i] = std::sqrt((square_sum_x - sum_x * sum_x / (window)) / (window - 1));
        }
        else if (partial == true and i >= least - 1) {
            ret[i] = std::sqrt((square_sum_x - sum_x * sum_x / (i + 1)) / i);
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_std.cpp")
// print(ts_std(1:5, 3))
