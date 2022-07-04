#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_argmax(
    const Rcpp::NumericVector& x,
    const int window,
    const int partial = false,
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

    for (int i = window - 1; i < x_size; i++) {
        ret[i] = i;
        for (int j = i; j > i - window; j--) {
            if (x[j] > x[ret[i]])
                ret[i] = j;
        }
    }

    if (partial == true) {
        for (int i = least - 1; i < window - 1; i++) {
            ret[i] = i;
            for (int j = i; j > i - window; j--) {
                if (x[j] > x[ret[i]])
                    ret[i] = j;
            }
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_sum.cpp")
// print(ts_argmax(1:5, 3)