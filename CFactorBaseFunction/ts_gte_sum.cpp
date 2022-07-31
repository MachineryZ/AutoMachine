#include <Rcpp.h>
#include <cstring>
#include <bits/stdc++.h>

//[[Rcoo::export]]
Rcpp::NumericVector ts_gte_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 1,
    const double fill = NA_REAL,
    const int method = 1,
    const double quantile = 0.5, 
    const double value,
) {

    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    if (!(method == 1 or method == 2 or method == 3))
        throw std::range_error("input method should be in 'mean' 'greater' 'quantile");

    for (int i = 0; i < x_size; i++) {
        
    }



    Rcpp::NumericVector ret(x_size, fill);

    return ret;
}
