#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_rank(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    // Args:
    //      x: input vector,
    //      window: rolling window size
    //      partial: if true, use least; if false, do not use least
    //      least: shortest window for ts_rank
    //      fill: how to fill nan
    // Returns:
    //      ret: the ts_rank result
    // Example:
    // input:
    // [1, 2, 2, 3, 1], window = 2
    //  1  2
    //     1.5 1.5
    //        1  2
    //           2  1
    // return:
    // [na,2,1.5,2, 1]

    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");
    
    Rcpp::NumericVector ret(x_size, fill);

    for (int i = window - 1; i < x_size; i++) {
        int greater = 0;
        int equal = 0;
        int lesser = 0;
        for (int j = i; j > i - window; j--) {
            if (x[j] == x[i])
                equal++;
            else if (x[j] > x[i])
                greater++;
            else if (x[j] < x[i])
                lesser++;
        }
        ret[i] = (2 * lesser + 1 + equal) / 2;
    }

    if (partial == true) {
        for (int i = least - 1; i < window - 1; i++) {
            int greater = 0;
            int equal = 0;
            int lesser = 0;
            for (int j = i; j > i - window; j--) {
                if (x[j] == x[i])
                    equal++;
                else if (x[j] > x[i])
                    greater++;
                else if (x[j] < x[i])
                    lesser++;
            }
            ret[i] = (2 * lesser + 1 + equal) / 2;
        }
    }
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_rank.cpp")
// print(ts_rank(c(1,1,2,2,2,5), 5))