#pragma once

#include <Eigen/Sparse>
#include <vector>

typedef Eigen::SparseMatrix<double, Eigen::ColMajor> SP_COL;
typedef Eigen::SparseMatrix<double, Eigen::RowMajor> SP_ROW;
typedef Eigen::SparseVector<double> SV;
typedef std::vector<std::pair<int, double>> IDX_SCORE_VEC;
typedef std::vector<std::pair<std::string, double>> ID_SCORE_VEC;

template<typename SP>
class KNN {

private:
  static IDX_SCORE_VEC calculate_simi(const SP &sp_mat,
                                      int idx,
                                      int another_idx,
                                      double simi_th);

public:
  static IDX_SCORE_VEC naive_kNearest(const SP &sp_mat,
                                      int idx,
                                      int another_idx,
                                      int k,
                                      double simi_th);
};
