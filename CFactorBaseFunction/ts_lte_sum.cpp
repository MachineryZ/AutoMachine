#include <Rcpp.h>
#include <cstring>
#include <bits/stdc++.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_gte_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 1,
    const double fill = NA_REAL,
    const int method = 1,
    const double quantile = 0.5, 
    const double value = 1.0
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    if (!(method == 1 or method == 2 or method == 3))
        throw std::range_error("input method should be in 'mean' 'greater' 'quantile");

    Rcpp::NumericVector ret(x_size, fill);

    for (int i = 0; i < x_size; i++) {
        double threshold = 0.0;
        if (i >= window - 1) {
            if (method == 1) { // quantile
                for (int j = i - window + 1; j <= i; j++) {
                    threshold += x[j];
                }
                threshold = threshold * quantile;
            }
            else if (method == 2) { // mean
                for (int j = i - window + 1; j <= i; j++) {
                    threshold += x[j];
                }
                threshold /= window;
            }
            ret[i] = 0.0;
            for (int j = i - window + 1; j <= i; j++) {
                ret[i] += (x[j] <= threshold) ? x[j] : 0.0;
            }
            ret[i] *= value;
        }
        else if (partial == true and i >= least - 1) {
            if (method == 1) { // quantile
                for (int j = 0; j <= i; j++) {
                    threshold += x[j];
                }
                threshold = threshold * quantile;
            }
            else if (method == 2) { // mean
                for (int j = 0; j <= i; j++) {
                    threshold += x[j];
                }
                threshold /= (i + 1);
            }
            ret[i] = 0.0;
            for (int j = 0; j <= i; j++) {
                ret[i] += (x[j] <= threshold) ? x[j] : 0.0;
            }
            ret[i] *= value;
        }
    }
    return ret;
}

/*
library("Rcpp")
sourceCpp(file="ts_gte_sum.cpp")
print(ts_gte_sum(c(1,2,3,4,4), 3, TRUE, 2, method=2))

*/

/*
library("Rcpp")
sourceCpp(file="ts_gte_sum.cpp")
print(ts_gte_sum(c(1,2,3,4,4), 3, TRUE, 2, method=2))

*/


/*
library("Rcpp")
sourceCpp(file="ts_gte_sum.cpp")
print(ts_gte_sum(c(1,2,3,4,4), 3, TRUE, 1, method=2))

*/
