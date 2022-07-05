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

    for (int i = window - 1; i < x_size; i++) {
        double mean = 0.0;
        ret[i] = 0.0;
        for (int j = i; j > i - window; j--) {
            mean += x[j];
        }
        mean = mean / window;
        for (int j = i; j > i - window; j--) {
            ret[i] += (x[j] - mean) * (x[j] - mean);
        }
        ret[i] = std::sqrt(ret[i] / (window - 1));
    }
    if (partial == true) {
        for (int i = window - 1; i < x_size; i++) {
            double mean = 0.0;
            ret[i] = 0.0;
            for (int j = i; j > i - least; j--) {
                mean += x[j];
            }
            mean = mean / window;
            for (int j = i; j > i - least; j--) {
                ret[i] += (x[j] - mean) * (x[j] - mean);
            }
            ret[i] = std::sqrt(ret[i] / (window - 1));
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_std.cpp")
// print(ts_std(1:5, 3))
