#include <iostream>
#include <bits/stdc++.h>
#include <Rcpp.h>

//[[Rcpp::export]]
double weighted_pearson_correlation(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const std::optional<Rcpp::NumericVector> w = std::nullopt,
) {
    // how to deal with nan ?
    int x_size = x.size();
    int y_size = y.size();
    if (x_size != y_size)
        throw std::range_error("the input vector should be in same size");

    double num = 0.0;
    double den_x = 0.0;
    double den_y = 0.0;
    double mean_x = 0.0;
    double mean_y = 0.0;
    
    for (int i = 0; i < x_size; i++) {
        mean_x += x[i];
        mean_y += y[i];
    }
    mean_x /= x_size;
    mean_y /= y_size;

    for (int i = 0; i < x_size; i++) {
        num += (x[i] - mean_x) * (y[i] - mean_y);
        den_x += (x[i] - mean_x) * (x[i] - mean_x);
        den_y += (y[i] - mean_y) * (y[i] - mean_y);
    }

    return num / (den_x + den_y);
}

double weighted_spearman_correlation(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const Rcpp::NumericVector& w
) {
    int x_size = x.size();
    int y_size = y.size();
    int w_size = w.size();
    if (x_size != y_size or y_size != w_size)
        throw std::range_error("the input vector should be in same size");
    
    double result = 0.0;

}

double mean_absolute_error(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const Rcpp::NumericVector& w
) {
    int x_size = x.size();
    int y_size = y.size();
    int w_size = w.size();
    if (x_size != y_size or y_size != w_size)
        throw std::range_error("the input vector should be in same size");
    
    double result = 0.0;
    return result;
}

double mean_square_error(
    const Rcpp::NumericVector& x,
    const Rcpp::NumericVector& y,
    const Rcpp::NumericVector& w
) {
    double result = 0.0;
    return result;
}

class Function:
{
private:
    std::string name;
    int arity;
public:
    Function (
        const std::string name_,
        const int arity_
    ) {
        name = name_;
        arity = arity_;
    }
    ~Function () {}
};

