#include "KNN.h"
#include <iostream>

auto comp_fn = [](const auto &a, const auto &b) { return a.second > b.second; };
auto comp_idx = [](const auto &a, const auto &b) { return a.first < b.first; };

template<typename SP>
IDX_SCORE_VEC KNN<SP>::calculate_simi(const SP &sp_mat, int idx, int another_idx,
                                      double simi_th) {
  // return vec of non-zero simi -> idx : simi
  IDX_SCORE_VEC simi;
  SV vec, tgt, another_tgt;

  // each row is a user
  // each col is a book
  // each entry is a rating

  // target : calculate user(specified by idx)-user(all or certain column) similarity
  if (sp_mat.IsRowMajor) {
    // user
    tgt = sp_mat.row(idx);
    if (another_idx != -1) {
      // item
      another_tgt = sp_mat.col(another_idx);
    }
  }
  // target : calculate item-item similarity
  else {
    // item
    tgt = sp_mat.col(idx);
    if (another_idx != -1) {
      // user
      another_tgt = sp_mat.row(another_idx);
    }
  }

  // vector norm
  double sqrt_bright = sqrt(tgt.cwiseProduct(tgt).sum());
  if (another_idx == -1) {
    for (int j = 0; j < sp_mat.outerSize(); ++j) {
      if (j == idx) continue;
      if (sp_mat.IsRowMajor) vec = sp_mat.row(j);
      else
        vec = sp_mat.col(j);
      double top = tgt.cwiseProduct(vec).sum();
      if (top != 0) {
        double sqrt_bleft = sqrt(vec.cwiseProduct(vec).sum());
        double s = top / (sqrt_bleft * sqrt_bright);
        if (s > simi_th)
          simi.emplace_back(j, s);
      }
    }
  } else {
    // we both rated this book
    for (int j = 0; j < another_tgt.nonZeros(); ++j) {
      int k = *(another_tgt.innerIndexPtr() + j);
      if (k == idx) continue;  // ignore self similarity
      if (sp_mat.IsRowMajor) vec = sp_mat.row(k);
      else
        vec = sp_mat.col(k);
      // denominator
      double top = tgt.cwiseProduct(vec).sum();
      if (top != 0) {
        double sqrt_bleft = sqrt(vec.cwiseProduct(vec).sum());
        double s = top / (sqrt_bleft * sqrt_bright);
        if (s > simi_th)
          simi.emplace_back(k, s);
      }
    }
  }
  return simi;
}

template<typename SP>
IDX_SCORE_VEC KNN<SP>::naive_kNearest(const SP &sp_mat, int idx, int another_idx,
                                      int k, double simi_th) {

  IDX_SCORE_VEC simi = calculate_simi(sp_mat, idx, another_idx, simi_th);
  std::sort(simi.begin(), simi.end(), comp_fn);
  if (k == -1)
    simi.resize((int) simi.size());
  else
    simi.resize(std::min(k, (int) simi.size()));
  std::sort(simi.begin(), simi.end(), comp_idx);

  return simi;
}

template class KNN<SP_COL>;
template class KNN<SP_ROW>;
