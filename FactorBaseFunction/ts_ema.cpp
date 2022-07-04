#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp:: NumericVector ts_ema(
    const Rcpp::NumericVector& x,
    const int window,
    const double beta,
    const bool partial = false,
    const int least = 0,
    
) {
    int x_size = x.size();
    

}
