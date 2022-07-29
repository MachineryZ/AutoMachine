#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_min(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    // Args:
    //      x: input vector,
    //      window: rolling window size, int
    //      partial: if true, use partial; if false, fill NA
    //      fill: how to fill nan, default NA_REAL
    // Returns:
    //      ret: ts_min result
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);
    std::multiset<double> s;
    
    for (int i = 0; i < x_size; i++) {
        s.insert(x[i]);
        if (i >= window) {
            s.erase(s.find(x[i - window]));
        }
        if (i >= window - 1) {
            ret[i] = *(s.begin());
        }
        else if (partial == true and i >= least - 1) {
            ret[i] = *(s.begin());
        }
    }
    return ret;
} 

// library("Rcpp")
// sourceCpp(file="ts_min.cpp")
// print(ts_min(1:5, 3))
