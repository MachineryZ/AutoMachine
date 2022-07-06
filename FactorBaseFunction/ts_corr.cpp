#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_corr(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    int y_size = y.size();
    if (x_size != y_size)
        throw std::range_error("input two vector dimension must be same");
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        double mean_x = 0.0;
        double mean_y = 0.0;
        double sigma_x = 0.0;
        double sigma_y = 0.0;
        double rho = 0.0;
        for (int j = i; j > i - window; j--) {
            mean_x += x[j];
            mean_y += y[j];
        }
        mean_x /= window;
        mean_y /= window;
        for (int j = i; j > i - window; j--) {
            sigma_x += (mean_x - x[j]) * (mean_x - x[j]);
            sigma_y += (mean_y - y[j]) * (mean_y - y[j]);
        }
        sigma_x = std::sqrt(sigma_x);
        sigma_y = std::sqrt(sigma_y);
        for (int j = i; j > i - window; j--) {
            rho += (x[j] - mean_x) * (y[j] - mean_y);
        }
        ret[i] = rho / sigma_x / sigma_y;
    }

    if (partial == true) {
        for (int i = least - 1; i < window - 1; i++) {
            double mean_x = 0.0;
            double mean_y = 0.0;
            double sigma_x = 0.0;
            double sigma_y = 0.0;
            double rho = 0.0;
            for (int j = i; j >= 0; j--) {
                mean_x += x[j];
                mean_y += y[j];
            }
            mean_x /= i + 1;
            mean_y /= i + 1;
            for (int j = i; j > i - window; j--) {
                sigma_x += (mean_x - x[j]) * (mean_x - x[j]);
                sigma_y += (mean_y - y[j]) * (mean_y - y[j]);
            }
            sigma_x = std::sqrt(sigma_x);
            sigma_y = std::sqrt(sigma_y);
            for (int j = i; j > i - window; j--) {
                rho += (x[j] - mean_x) * (y[j] - mean_y);
            }
            ret[i] = rho / sigma_x / sigma_y;
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_corr.cpp")
// print(ts_corr(c(1,2,3,5,4), c(5,4,3,2,1), 3))
// nan nan -1 -0.981981 -0.5
