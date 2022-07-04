#include <Rcpp.h>
#include <bits/stdc++.h>
#include <set>
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


    // for (int i = window - 1; i < x_size; i++) {
    //     std::multiset<double, std::vector<double>, std::greater<double>> minheap;
    //     std::multiset<double, std::vector<double>, lesser<double>> maxheap;
    //     for (int j = i)
    // }
    std:multiset<double> min_set;
    std:multiset<double> max_set;
    for (int i = 0; i < x_size; i++) {
        if (partial == true and i <= lesat - 1) {
            
        }
    }

    return ret;
}

// library("Rcpp")
// sourceCpp(file="ts_median.cpp")
// print(ts_median(1:5, 3))


