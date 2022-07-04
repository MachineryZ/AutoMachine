#include <Rcpp.h>
#include <bits/stdc++.h>
#include <queue>
#include <vector>

bool lesser(double a, double b)
{return a < b;}

//[[Rcpp::export]]
Rcpp::NumericVector ts_median(
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

    // std::priority_queue<double, std::vector<double>, std::greater<double>> pq;

    for (int i = window - 1; i < x_size; i++) {
        std::priority_queue<double, std::vector<double>, std::greater<double>> minheap;
        std::priority_queue<double, std::vector<double>, lesser<double>> maxheap;
    }

    return ret;
}

// library("Rcpp")
// sourceCpp(file="ts_median.cpp")
// print(ts_median(1:5, 3))
