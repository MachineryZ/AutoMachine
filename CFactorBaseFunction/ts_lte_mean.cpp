#include <Rcpp.h>
#include <cstring>
#include <bits/stdc++.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_lte_mean(
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
    std::set<double> s;
    double threshold = 0.0;
    double sum = 0.0;

    for (int i = 0; i < x_size; i++) {
        s.insert(x[i]);
        sum += x[i];
        int cnt = 0;
        if (i > window - 1) {
            s.erase(x[i - window]);
            sum -= x[i - window];
        }
        if (i >= window - 1) {
            if (method == 1) { // quantile
                int rank = int(quantile * window);
                auto it = s.begin();
                while(rank > 0) {
                    it++;
                    rank--;
                }
                if (it == --s.end())
                    threshold = *it;
                else {
                    auto it_copy = it;
                    it_copy++;
                    threshold = *it + (*it_copy - *it) * 
                        (quantile - double(int(quantile * window)));
                }
                ret[i] = 0.0;
                for (int j = i - window + 1; j <= i; j++) {
                    if (x[j] <= threshold) {
                        cnt++;
                        ret[i] += x[j];
                    }
                }
                ret[i] *= value;
                ret[i] /= cnt;
            }
            else if (method == 2) {
                threshold = sum / window;
                ret[i] = 0.0;
                for (int j = i - window + 1; j <= i; j++) {
                    if (x[j] <= threshold) {
                        cnt++;
                        ret[i] += x[j];
                    }
                }
                ret[i] *= value;
                ret[i] /= cnt;
            }
            
        }
        else if (partial == true and i >= least - 1) {
            if (method == 1) { // quantile
                int rank = int(quantile * window);
                auto it = s.begin();
                while(rank > 0) {
                    it++;
                    rank--;
                }
                if (it == --s.end())
                    threshold = *it;
                else {
                    auto it_copy = it;
                    it_copy++;
                    threshold = *it + (*it_copy - *it) * 
                        (quantile - double(int(quantile * (i + 1)))) * (i + 1);
                }
                ret[i] = 0.0;
                for (int j = 0; j <= i; j++) {
                    if (x[j] <= threshold) {
                        cnt++;
                        ret[i] += x[j];
                    }
                }
                ret[i] *= value;
                ret[i] /= cnt;
            }
            else if (method == 2) {
                threshold = sum / (i + 1);
                ret[i] = 0.0;
                for (int j = 0; j <= i; j++) {
                    if (x[j] <= threshold) {
                        cnt++;
                        ret[i] += x[j];
                    }
                }
                ret[i] *= value;
                ret[i] /= cnt;
            }
        }
    }
    return ret;

}

/*
library("Rcpp")
sourceCpp(file="ts_lte_mean.cpp")
print(ts_lte_mean(c(1,2,3,4,4), 3, TRUE, 2, method=2))

library("Rcpp")
sourceCpp(file="ts_lte_mean.cpp")
print(ts_lte_mean(c(1,2,3,4,4), 3, TRUE, 2, method=1))

*/
