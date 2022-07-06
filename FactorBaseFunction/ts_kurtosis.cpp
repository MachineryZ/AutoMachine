#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_kurtosis(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        double mean_x = 0.0;
        double sigma_x = 0.0;
        double k_x = 0.0;
        for (int j = i; j > i - window; j--) {
            mean_x += x[j];
        }
        mean_x /= window;
        for (int j = i; j > i - window; j--) {
            sigma_x += (mean_x - x[j]) * (mean_x - x[j]);
            k_x += (x[j] - mean_x) * (x[j] - mean_x) * (x[j] - mean_x) * (x[j] - mean_x);
        }
        sigma_x = std::sqrt(sigma_x/(window - 1));
        ret[i] = k_x / sigma_x / sigma_x / sigma_x / sigma_x / window;
    }

    if (partial == true) {
        for (int i = least - 1; i < window - 1; i++) {
            double mean_x = 0.0;
            double sigma_x = 0.0;
            double k_x = 0.0;
            for (int j = i; j > i - window; j--) {
                mean_x += x[j];
            }
            mean_x /= least;
            for (int j = i; j > i - window; j--) {
                sigma_x += (x[j] - mean_x) * (x[j] - mean_x);
                k_x += (x[j] - mean_x) * (x[j] - mean_x) * (x[j] - mean_x) * (x[j] - mean_x);
            }
            sigma_x = std::sqrt(sigma_x / (i - 1));
            ret[i] = k_x / sigma_x / sigma_x / sigma_x / sigma_x / i;
        }
    }
    return ret;
}
// libraray("Rcpp")
// sourceCpp("ts_skewness.cpp")
// print(ts_skewness(c(1,2,3,5), 4))
// print(0.23823139)