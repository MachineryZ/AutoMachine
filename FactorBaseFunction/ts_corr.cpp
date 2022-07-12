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

    double sum_x = 0.0;
    double sum_y = 0.0;
    double square_sum_x = 0.0;
    double square_sum_y = 0.0;
    double cross_xy = 0.0;

    for (int i = 0; i < x_size; i++) {
        sum_x += x[i];
        sum_y += y[i];
        square_sum_x += x[i] * x[i];
        square_sum_y += y[i] * y[i];
        cross_xy += x[i] * y[i];
        if (partial == true and i >= least - 1) {
            ret[i] = (cross_xy - sum_x / (i + 1) * sum_y - sum_y / (i + 1) * sum_x + sum_x * sum_y / (i + 1)) / 
                    std::sqrt(square_sum_x - 2 * sum_x / (i + 1) * sum_x + sum_x * sum_x / (i + 1)) / 
                    std::sqrt(square_sum_y - 2 * sum_y / (i + 1) * sum_y + sum_y * sum_y / (i + 1));
        }
        else if (i >= window - 1) {
            if (i >= window) {
                sum_x -= x[i - window];
                sum_y -= y[i - window];
                square_sum_x -= x[i - window] * x[i - window];
                square_sum_y -= y[i - window] * y[i - window];
                cross_xy -= x[i - window] * y[i - window];
                }
            ret[i] = (cross_xy - sum_x / window * sum_y - sum_y / window * sum_x + sum_x * sum_y / window) / 
                    std::sqrt(square_sum_x - 2 * sum_x / window * sum_x + sum_x * sum_x / window) / 
                    std::sqrt(square_sum_y - 2 * sum_y / window * sum_y + sum_y * sum_y / window);
        }
    }

    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_corr.cpp")
// print(ts_corr(c(1,2,3,5,4), c(5,4,3,2,1), 3))
// nan nan -1 -0.981981 -0.5
