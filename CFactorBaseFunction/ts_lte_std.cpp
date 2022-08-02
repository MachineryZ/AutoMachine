#include <Rcpp.h>
#include <cstring>
#include <bits/stdc++.h>


//[[Rcpp::export]]
Rcpp::NumericVector ts_gte_sd(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 2,
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
    double square_sum = 0.0;
    double cnt = 0.0;

    for (int i = 0; i < x_size; i++) {
        s.insert(x[i]);
        sum = 0.0;
        square_sum = 0.0;
        cnt = 0.0;
        if (i > window - 1) {
            s.erase(x[i - window]);
        }
        if (i >= window - 1 or (partial == true and i >= least - 1)) {
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
                    auto it_copy = it;;
                    it_copy++;
                    threshold = *it + (*it_copy - *it) * 
                        (quantile - double(int(quantile * window)));
                }
                ret[i] = 0.0;
                for (int j = i - window + 1; j <= i; j++) {
                    if (x[j] >= threshold) {
                        sum += x[j];
                        square_sum += x[j] * x[j];
                        cnt++;
                    }
                }
                ret[i] = value * std::sqrt((square_sum - sum * sum / cnt) / (cnt - 1));
            }
            else if (method == 2) {
                threshold = sum / window;
                ret[i] = 0.0;
                for (int j = i - window + 1; j <= i; j++) {
                    if (x[j] >= threshold) {
                        sum += x[j];
                        square_sum += x[j] * x[j];
                        cnt++;
                    }
                }
                ret[i] = value * std::sqrt((square_sum - sum * sum / (cnt)) / (cnt - 1));
            }
        }
        std::cout << "threshold = " << threshold << std::endl;
    }
    return ret;
}
/*
library("Rcpp")
sourceCpp(file="ts_gte_sd.cpp")
print(ts_gte_sd(c(1,2,3,4,5), 3, TRUE, 2 ,method=1))
*/