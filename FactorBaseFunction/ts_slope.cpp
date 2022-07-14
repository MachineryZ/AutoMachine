#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_slope(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    // w = (xi - mean_x) * (yi - mean_y) / (x_i - mean_x)**2
    // b = mean_y - w mean_x
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 1)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        ret[i] = 0;
        double mean_x = 0;
        double mean_y = double(window - 1) / 2;
        double den = 0.0;
        for (int j = i; j > i - window; j--) {
            mean_x += x[j];
        }
        mean_x /= window;
        for (int j = 0; j < window; j++) {
            ret[i] += (x[i - window + 1 + j] - mean_x) * (j - mean_y);
            den += (j - mean_y) * (j - mean_y);
        }
        ret[i] /= den;
    }

    if (partial == true) {
        for (int i = least - 1; i < window - 1; i++) {
            ret[i] = 0;
            double mean_x = 0;
            double mean_y = double(window - 1) / 2;
            double den = 0.0;
            for (int j = 0; j <= i; j++) {
                mean_x += x[j];
            }
            mean_x /= (i + 1);
            for (int j = 0; j <= i; j++) {
                ret[i] += (x[j] - mean_x) * (j - mean_y);
                den += (j - mean_y) * (j - mean_y);
            }
            ret[i] /= den;
        }
    }

    return ret;
}
// library("Rcpp")
// sourceCpp("ts_slope.cpp")
// print(ts_slope(c(1,2,3,4,6,8), 3))
//  NA  NA 1.0 1.0 1.5 2.0
