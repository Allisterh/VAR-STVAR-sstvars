#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

//' @name get_multisets_Cpp
//' @title Generate all d-element multisets
//' @description Generates all d-element multisets in \eqn{\lbrace 1,...,n \rbrace}
//'   ordered in a lexicographic order.
//'
//' @param n positive integer specifying the value n in \eqn{\lbrace 1,...,n \rbrace}.
//' @param d positive integer specifying the size of the multisets.
//' @param N the binomial coefficient \code{choose(n + d - 1, d)} (calculated in R wrapper)
//' @details This function is used in approximation of the joint spectral radius.
//' @return a numeric matrix with N rows and d columns, containing each multiset in each row, ordered
//'   lexicographically from top to bottom.
//' @keywords internal
// [[Rcpp::export]]
arma::mat get_multisets_Cpp(int n, int d, arma::uword N) {
  if (n <= 0 || d < 0) {
    throw std::runtime_error("n must be a strictly positive integer and d must be a non-negative integer.");
  }

  arma::mat result_matrix(N, d);
  arma::rowvec current_multiset(d, arma::fill::ones);
  arma::uword row_index = 0;

  while (row_index < N) {
    result_matrix.row(row_index) = current_multiset;
    row_index++;

    for (int i = d - 1; i >= 0; --i) {
      if (current_multiset[i] < n) {
        current_multiset[i]++;
        if (i < d - 1) {
          current_multiset.subvec(i + 1, d - 1).fill(current_multiset[i]);
        }
        break;
      }
    }
  }

  return result_matrix;
}