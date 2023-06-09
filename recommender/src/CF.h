#pragma once

#include "InputReader.h"
#include "KNN.h"
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>


class CF {
private:
  InputReader &input;

  template<typename SP>
  [[nodiscard]] double predict_ui_rating(int idx, const IDX_SCORE_VEC &idx_score) const;

public:
  explicit CF(InputReader &input) : input(input){};

  template<typename SP>
  double test_rmse(double avg_value,
                   int k = -1,
                   double simi_th = 0,
                   bool keep_nonzero_topk = true);

  ID_SCORE_VEC recommended_items_for_user(const std::string &user_id,
                                          const std::string &based,
                                          int k = -1,
                                          double simi_th = 0,
                                          int n = 10,
                                          bool keep_nonzero_topk = true);
  ID_SCORE_VEC recommended_users_for_item(const std::string &item_id,
                                          const std::string &based,
                                          int k = -1,
                                          double simi_th = 0,
                                          int n = 10,
                                          bool keep_nonzero_topk = true);
  ID_SCORE_VEC recommend(const std::string &tgt,
                         const std::string &id,
                         const std::string &based,
                         int k = -1,
                         double simi_th = 0,
                         int n = 10,
                         bool keep_nonzero_topk = true);
};
