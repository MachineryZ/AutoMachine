#include <Rcpp.h>
#include <cmath>

//[[Rcpp::export]]
Rcpp::NumericVector ts_stddev(
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

    Rcpp::NumericVector ret(x_size, fill);

    double sum_x = 0.0;
    double square_sum_x = 0.0;

    for (int i = 0; i < x_size: i++) {
        sum_x += x[i];
        square_sum_x += x[i] * x[i];
        if (i > window - 1) {
            sum_x -= x[i];
            square_sum_x -= x[i] * x[i];
        }
    }

    // for (int i = window - 1; i < x_size; i++) {
    //     double mean = 0.0;
    //     ret[i] = 0.0;
    //     for (int j = i; j > i - window; j--) {
    //         mean += x[j];
    //     }
    //     mean = mean / window;
    //     for (int j = i; j > i - window; j--) {
    //         ret[i] += (x[j] - mean) * (x[j] - mean);
    //     }
    //     ret[i] = std::sqrt(ret[i] / (window - 1));
    // }
    // if (partial == true) {
    //     for (int i = least - 1; i < window - 1; i++) {
    //         double mean = 0.0;
    //         ret[i] = 0.0;
    //         for (int j = i; j >= 0; j--) {
    //             mean += x[j];
    //         }
    //         mean = mean / window;
    //         for (int j = i; j >= 0; j--) {
    //             ret[i] += (x[j] - mean) * (x[j] - mean);
    //         }
    //         ret[i] = std::sqrt(ret[i] / i);
    //     }
    // }
    // return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_std.cpp")
// print(ts_std(1:5, 3))
