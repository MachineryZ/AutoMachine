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
            ret[i] = cross_xy - sum_x / (i + 1) * sum_y;
        }
    }

    // for (int i = window - 1; i < x_size; i++) {
    //     ret[i] = 0.0;
    //     double mean_x = 0.0;
    //     double mean_y = 0.0;
    //     for (int j = i; j > i - window; j--) {
    //         mean_x += x[j];
    //         mean_y += y[j];
    //     }
    //     mean_x /= window;
    //     mean_y /= window;
    //     for (int j = i; j > i - window; j--) {
    //         ret[i] += (x[j] - mean_x) * (y[j] - mean_y);
    //     }
    //     ret[i] /= (window - 1);
    // }

    // if (partial == true) {
    //     for (int i = least - 1; i < window - 1; i++) {
    //         ret[i] = 0.0;
    //         double mean_x = 0.0;
    //         double mean_y = 0.0;
    //         for (int j = i; j >= 0; j--) {
    //             mean_x += x[j];
    //             mean_y += y[j];
    //         }
    //         mean_x /= i + 1;
    //         mean_y /= i + 1;
    //         for (int j = i; j > i - least; j--) {
    //             ret[i] += (x[j] - mean_x) * (y[j] - mean_y);
    //         }
    //         ret[i] /= (window - 1);
    //     }
    // }
    // return ret;
}

// library("Rcpp")
// sourceCpp(file="ts_cov.cpp")
// print(ts_cov(c(1,2,3,5,4), c(1,2,3,4,5), 3))