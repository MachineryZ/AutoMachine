#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const int weight,
    const double fill = NA_REAL
) {
    std::cout << "fill = " << fill << std::endl;
    int x_size = x.size();
    Rcpp::NumericVector ret(x_size, fill);
    std::cout << ret << std::endl;
    for(int i = window - 1; i < x_size; i++) {
        ret[i] = 0.0;
        for(int j = i; j > i - window; j--) {
            ret[i] += x[j];
        }
    }
    return ret;
}


library("Rcpp")
sourceCpp(code='
#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_sum(
    const Rcpp::NumericVector& x,
    const int window,
    const int weight,
    const double fill = NA_REAL
) {
    std::cout << "fill = " << fill << std::endl;
    int x_size = x.size();
    Rcpp::NumericVector ret(x_size, fill);
    std::cout << ret << std::endl;
    for(int i = window - 1; i < x_size; i++) {
        ret[i] = 0.0;
        for(int j = i; j > i - window; j--) {
            ret[i] += x[j];
        }
    }
    return ret;
}

')
print(ts_sum(1:5, 5, 1, 0.0))

(x, window, weight, intercept = TRUE, sign= 0L, skip =0L, partial =FALSE,  least = 3L, fill= NA_real_, threads= 1L, last= 0L)
