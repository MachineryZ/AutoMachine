#include <Rcpp.h>

//[[Rcpp::export]]
Rcpp::NumericVector ts_argmin(
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
    std::multiset<std::pair<double, int>> m_set;
    for (int i = 0; i < x_size; i++) {
        m_set.insert(std::make_pair(x[i], i));
        if (m_set.size() > window) {
            m_set.erase(m_set.find(std::make_pair(x[i - window], i - window)));
        }
        if (partial == true and (least - 1 <= i and i < window - 1)) {
            ret[i] = (m_set.begin())->second;
        }
        else if (i >= window - 1) {
            ret[i] = (m_set.begin())->second - (i - window + 1);
        }
    }
    
    return ret;
}
// library("Rcpp")
// sourceCpp(file="ts_argmin.cpp")
// print(ts_argmin(c(1,2,5,3,1), 3))