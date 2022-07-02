#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

//[[Rcpp::export]]
int hello(){
    cout << "Hello, World!";
    return 0;
}

/*** R
hello()
*/