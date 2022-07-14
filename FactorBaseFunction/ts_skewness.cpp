#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_skewness(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 2,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);
    double sum_x = 0;
    double square_sum_x = 0.0;
    double cube_sum_x = 0.0;

    for (int i = 0; i < x_size; i++) {
        sum_x += x[i];
        square_sum_x += x[i] * x[i];
        cube_sum_x += x[i] * x[i] * x[i];
        if (i > window - 1) {
            sum_x -= x[i - window];
            square_sum_x -= x[i - window] * x[i - window];
            cube_sum_x -= x[i - window] * x[i - window] * x[i - window];
        }
        if (i >= window - 1) {
            double sigma_x = std::sqrt((square_sum_x - sum_x * sum_x / window) / (window - 1));
            double k_x = cube_sum_x - \
                3 * square_sum_x * sum_x / window + \
                2 * sum_x * sum_x * sum_x / window / window;
            ret[i] = k_x / sigma_x / sigma_x / sigma_x / window;
        }
        else if (partial == true and i >= least - 1) {
            double sigma_x = std::sqrt((square_sum_x - sum_x * sum_x / (i + 1)) / i);
            double k_x = cube_sum_x - \
                3 * square_sum_x * sum_x / (i + 1) + \
                2 * sum_x * sum_x * sum_x / (i + 1) / (i + 1);
            ret[i] = k_x / sigma_x / sigma_x / sigma_x / (i + 1);
        }
    }
    return ret;
}
// libraray("Rcpp")
// sourceCpp("ts_skewness.cpp")
// print(ts_skewness(c(1,2,3,5), 4))
// print(0.23823139)
