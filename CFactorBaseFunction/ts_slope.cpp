#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_slope(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    // w = sum(xi - mean_x) * (i - mean_i) / (i - mean_i)**2
    // b = mean_x - w mean_i
    // w = (sum_x * sum_i - sum_x * sum_i / n) / (i - mean_i)
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 1)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);
    double sum_x = 0.0;
    double sum_i = 0.0;
    double square_sum_i = 0.0;
    double cross_xi = 0.0;

    for (int i = 0; i < x_size; i++) {
        sum_x += x[i];
        sum_i += i;
        square_sum_i += i * i;
        cross_xi += x[i] * i;
        if (i > window - 1) {
            sum_x -= x[i - window];
            sum_i -= i - window;
            square_sum_i -= (i - window) * (i - window);
            cross_xi -= x[i - window] * (i - window);
        }
        if (i >= window - 1) {
            ret[i] = (cross_xi - sum_x * sum_i / window) / (square_sum_i - sum_i * sum_i / window); 
        }
        else if (partial == true and i >= least - 1) {
            ret[i] = (cross_xi - sum_x * sum_i / (i + 1)) / (square_sum_i - sum_i * sum_i / (i + 1)); 
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp("ts_slope.cpp")
// print(ts_slope(c(1,2,3,4,6,8), 3))
//  NA  NA 1.0 1.0 1.5 2.0
