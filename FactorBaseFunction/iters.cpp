#include <Rcpp.h>
using namespace Rcpp;

//[[Rcpp::export]]
NumericVector iters(NumericVector x){
  int n = x.size();
  NumericVector y(n);
  
  y[0] = x[0];
  double sign=-1;
  for(int t=1; t<n; t++){
    sign *= -1;
    y[t] = sign*y[t-1] + x[t];
  }
  
  return y;
}

