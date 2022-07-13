#include <Rcpp.h>
#include <cstring>
#include <bits/stdc++.h>

//[[Rcoo::export]]
Rcpp::NumericVector ts_gte_max(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 1,
    const double fill = NA_REAL,
    const string method = "mean",
    const double quantile = 0.5
) {

    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    double threshold = 0.0;
    if !(method == "greater" or method == "quantile" or method == "mean")
        throw std::range_error("input method should be in 'mean' 'greater' 'quantile");
    


    Rcpp::NumericVector ret(x_size, fill);

    return ret;
}