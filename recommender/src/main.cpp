#include "CF.h"
#include "InputReader.h"
#include <iostream>

int main() {
  //    const std::string rating = "../data/data/u1.base";
  //    const std::string test_rating = "../data/data/u1.test";
  //    auto input = InputReader(rating, test_rating);
  //    input.parse("train", "\t", false, false);
  //    input.parse("test", "\t", false, false);
  //    CF cf(input);
  //    auto items = cf.recommended_items_for_user("1", "user-based");
  //    cf.test_rmse<SP_ROW>(-1, 40, 0, true);

  const std::string book_train = "../data/Book_reviews/Book_reviews/BX-Book-Ratings-train.csv";
  const std::string book_test = "../data/Book_reviews/Book_reviews/BX-Book-Ratings-test.csv";
  auto input = InputReader(book_train, book_test);
  input.parse("train", ";", true, true);
  input.parse("test", ";", true, true);
  CF cf(input);
  auto items = cf.recommended_items_for_user("8", "user-based",
                                             40, 0, 10, false);
  //    auto users = cf.recommended_users_for_item("88740", 300);
  //    cf.test_rmse<SP_ROW>(-1, 40, 0, false);
}
