#include <Rcpp.h>
#include <bits/stdc++.h>
#include <set>
#include <vector>

bool lesser(double a, double b)
{return a < b;}

//[[Rcpp::export]]
Rcpp::NumericVector ts_median(
    const Rcpp::NumericVector& x,
    const int window,
    const bool partial = false,
    const int least = 0,
    const double fill = NA_REAL
) {
    int x_size = x.size();
    if (x_size == 0)
        return x;
    if (window <= 0)
        throw std::range_error("window must be a positive integer");

    Rcpp::NumericVector ret(x_size, fill);

    std::multiset<double> min_set;
    std::multiset<double> max_set;
    for (int i = 0; i < x_size; i++) {
        // insert x[i]
        if (max_set.size() > 0 and x[i] < *(max_set.begin()))
            min_set.insert(x[i]);
        else {
            max_set.insert(x[i]);
        }

        // check size
        if (min_set.size() == max_set.size() + 2) {
            double max_min = *(--min_set.end());
            min_set.erase(--min_set.end());
            max_set.insert(max_min);
        }
        else if(min_set.size() == max_set.size() - 2) {
            double max_min = *(max_set.begin());
            max_set.erase(max_set.begin());
            min_set.insert(max_min);
        }

        if (min_set.size() + max_set.size() > window) {
            // erase x[i - least + 1]
            if ((min_set.size() > 0) and (x[i - window] <= *(--min_set.end()))) {
                // std::cout << "erase min_set " << x[i - window] << std::endl;
                min_set.erase(x[i - window]);
            }
            else {
                // std::cout << "erase max_set " << x[i - window] << std::endl;
                max_set.erase(x[i - window]);
            }
        }

        if (min_set.size() == max_set.size() + 2) {
            double max_min = *(--min_set.end());
            min_set.erase(--min_set.end());
            max_set.insert(max_min);
        }
        else if(min_set.size() == max_set.size() - 2) {
            double max_min = *(max_set.begin());
            max_set.erase(max_set.begin());
            min_set.insert(max_min);
        }

        if ((partial == true and i >= least - 1) or i >= window - 1) {
            if ((min_set.size() + max_set.size()) % 2 == 0) {
                ret[i] = double((*(--min_set.end()) + *(max_set.begin())))/2;
            }
            else if ((min_set.size() + max_set.size()) % 2 == 1) {
                ret[i] = min_set.size() > max_set.size() ? *(--min_set.end()) : *(max_set.begin());
            } 
        }

        // std::cout << "min_set"; 
        // for (auto it = min_set.begin(); it != min_set.end(); it++) {
        //     std::cout << *it << " ";
        // } std::cout << std::endl;
        // std::cout << "max_set"; 
        // for (auto it = max_set.begin(); it != max_set.end(); it++) {
        //     std::cout << *it << " ";
        // } std::cout << std::endl << std::endl;

    }
    return ret;
}

// library("Rcpp")
// sourceCpp(file="ts_median.cpp")
// print(ts_median(1:10, 3))
// print(ts_median(1:10, 4))
// print(ts_median(1:10, 3, TRUE, 1))
// print(ts_median(1:10, 4, TRUE, 2))


