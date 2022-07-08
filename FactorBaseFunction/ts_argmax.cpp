#include <Rcpp.h>
#include <set>
#include <bits/stdc++.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_argmax(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 1,
    const double fill = NA_REAL
) {
    // Args:
    //      x: input vectr

    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);
    std::multiset<pair<int, double>> try_set;
    for (int i = 0; i < x_size; i++) {
        m_set.insert(make_pair(x[i], i));
        if (m_set.size() > window) {
            m_set.erase(m_set.find(make_pair(x[i - window], i - window)));
        }
        if (partial == true and (least - 1 <= i and i < window - 1)) {
            ret[i] = m_set.begin().second;
        }
        else {
            ret[i] = *m_set.begin();
        }
    }

    // for (int i = window - 1; i < x_size; i++) {
    //     ret[i] = 0;
    //     for (int j = i; j > i - window; j--) {
    //         if (x[j] > x[i - window + 1 + ret[i]])
    //             ret[i] = j - i + window - 1;
    //     }
    // }

    // if (partial == true) {
    //     for (int i = least - 1; i < window - 1; i++) {
    //         ret[i] = 0;
    //         for (int j = i; j >= 0; j--) {
    //             if (x[j] > x[ret[i]])
    //                 ret[i] = j;
    //         }
    //     }
    // }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_argmax.cpp")
// print(ts_argmax(c(1,5,4,3,5,4,10,2,2,2,1,1), 3, TRUE, 1))