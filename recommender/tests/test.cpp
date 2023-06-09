#include <random>
#include <gtest/gtest.h>
#include <KNN.h>
#include <CF.h>
#include <InputReader.h>

template<typename SP>
SP make_matrix() {
    SP sp_mat(8, 8);
    std::vector<Eigen::Triplet<double>> triplets;
    triplets.emplace_back(Eigen::Triplet<double>(0, 0, 4));
    triplets.emplace_back(Eigen::Triplet<double>(0, 1, 10));
    triplets.emplace_back(Eigen::Triplet<double>(0, 3, 1));
    triplets.emplace_back(Eigen::Triplet<double>(0, 5, 5));
    triplets.emplace_back(Eigen::Triplet<double>(0, 7, 4));

    triplets.emplace_back(Eigen::Triplet<double>(1, 1, 6));
    triplets.emplace_back(Eigen::Triplet<double>(1, 2, 4));
    triplets.emplace_back(Eigen::Triplet<double>(1, 3, 8));
    triplets.emplace_back(Eigen::Triplet<double>(1, 5, 8));
    triplets.emplace_back(Eigen::Triplet<double>(1, 6, 7));

    triplets.emplace_back(Eigen::Triplet<double>(2, 0, 8));
    triplets.emplace_back(Eigen::Triplet<double>(2, 1, 7));
    triplets.emplace_back(Eigen::Triplet<double>(2, 4, 2));
    triplets.emplace_back(Eigen::Triplet<double>(2, 5, 8));
    triplets.emplace_back(Eigen::Triplet<double>(2, 6, 8));
    triplets.emplace_back(Eigen::Triplet<double>(2, 7, 5));

    triplets.emplace_back(Eigen::Triplet<double>(3, 0, 5));
    triplets.emplace_back(Eigen::Triplet<double>(3, 2, 6));
    triplets.emplace_back(Eigen::Triplet<double>(3, 4, 2));
    triplets.emplace_back(Eigen::Triplet<double>(3, 5, 1));
    triplets.emplace_back(Eigen::Triplet<double>(3, 6, 3));
    triplets.emplace_back(Eigen::Triplet<double>(3, 7, 4));

    triplets.emplace_back(Eigen::Triplet<double>(4, 0, 9));
    triplets.emplace_back(Eigen::Triplet<double>(4, 1, 9));
    triplets.emplace_back(Eigen::Triplet<double>(4, 3, 7));
    triplets.emplace_back(Eigen::Triplet<double>(4, 4, 3));
    triplets.emplace_back(Eigen::Triplet<double>(4, 5, 10));
    triplets.emplace_back(Eigen::Triplet<double>(4, 6, 1));

    triplets.emplace_back(Eigen::Triplet<double>(5, 1, 4));
    triplets.emplace_back(Eigen::Triplet<double>(5, 2, 2));
    triplets.emplace_back(Eigen::Triplet<double>(5, 4, 4));
    triplets.emplace_back(Eigen::Triplet<double>(5, 5, 10));
    triplets.emplace_back(Eigen::Triplet<double>(5, 7, 4));

    triplets.emplace_back(Eigen::Triplet<double>(6, 1, 8));
    triplets.emplace_back(Eigen::Triplet<double>(6, 2, 11));
    triplets.emplace_back(Eigen::Triplet<double>(6, 3, 11));
    triplets.emplace_back(Eigen::Triplet<double>(6, 5, 2));
    triplets.emplace_back(Eigen::Triplet<double>(6, 6, 3));
    triplets.emplace_back(Eigen::Triplet<double>(6, 7, 7));

    triplets.emplace_back(Eigen::Triplet<double>(7, 0, 11));
    triplets.emplace_back(Eigen::Triplet<double>(7, 1, 1));
    triplets.emplace_back(Eigen::Triplet<double>(7, 2, 7));
    triplets.emplace_back(Eigen::Triplet<double>(7, 3, 10));
    triplets.emplace_back(Eigen::Triplet<double>(7, 5, 6));
    triplets.emplace_back(Eigen::Triplet<double>(7, 7, 1));

    sp_mat.setFromTriplets(triplets.begin(), triplets.end());

    return sp_mat;
}

TEST(KNNTest, KNN_user0_all) {
    auto sp_mat = make_matrix<SP_ROW>();
    IDX_SCORE_VEC result = KNN<SP_ROW>::naive_kNearest(sp_mat, 0, -1, 3, 0.5);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[1].first, 4);
    EXPECT_NEAR( result[1].second, 0.812587, 1e-6);

    EXPECT_EQ(result[0].first, 2);
    EXPECT_NEAR(result[0].second, 0.784340, 1e-6);

    EXPECT_EQ(result[2].first, 5);
    EXPECT_NEAR(result[2].second, 0.683999, 1e-6);
}

TEST(KNNTest, KNN_user0_nonZero) {
    auto sp_mat = make_matrix<SP_ROW>();
    IDX_SCORE_VEC result = KNN<SP_ROW>::naive_kNearest(sp_mat, 0, 3, -1, 0.3);
    EXPECT_EQ(result.size(), 4);

    EXPECT_EQ(result[1].first, 4);
    EXPECT_NEAR( result[1].second, 0.812587, 1e-6);

    EXPECT_EQ(result[0].first, 1);
    EXPECT_NEAR(result[0].second, 0.567777, 1e-6);

    EXPECT_EQ(result[2].first, 6);
    EXPECT_NEAR(result[2].second, 0.534980, 1e-6);
}

TEST(KNNTest, KNN_item0_all) {
    auto sp_mat = make_matrix<SP_COL>();
    IDX_SCORE_VEC result = KNN<SP_COL>::naive_kNearest(sp_mat, 0, -1, 3, 0.5);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[2].first, 5);
    EXPECT_NEAR( result[2].second, 0.704448, 1e-6);

    EXPECT_EQ(result[0].first, 1);
    EXPECT_NEAR(result[0].second, 0.576002, 1e-6);

    EXPECT_EQ(result[1].first, 3);
    EXPECT_NEAR(result[1].second, 0.551927, 1e-6);
}

TEST(KNNTest, KNN_item0_nonZero) {
    auto sp_mat = make_matrix<SP_COL>();
    IDX_SCORE_VEC result = KNN<SP_COL>::naive_kNearest(sp_mat, 0, 5, 3, 0.5);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[2].first, 5);
    EXPECT_NEAR( result[2].second, 0.704448, 1e-6);

    EXPECT_EQ(result[0].first, 1);
    EXPECT_NEAR(result[0].second, 0.576002, 1e-6);

    EXPECT_EQ(result[1].first, 4);
    EXPECT_NEAR(result[1].second, 0.526562, 1e-6);
}

TEST(CFTest, recommended_items_for_user_user_based) {
    auto tmp = InputReader(make_matrix<SP_COL>());
    CF cf(tmp);
    ID_SCORE_VEC result = cf.recommended_items_for_user("0", "user-based", 3,
                                                        0.5, 10, false);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0].first, "6");
    EXPECT_NEAR(result[0].second, 4.43809, 1e-5);

    EXPECT_EQ(result[1].first, "4");
    EXPECT_NEAR(result[1].second, 2.95601, 1e-5);

    EXPECT_EQ(result[2].first, "2");
    EXPECT_NEAR(result[2].second, 2, 1e-5);
}

TEST(CFTest, recommended_items_for_user_item_based) {
    auto tmp = InputReader(make_matrix<SP_COL>());
    CF cf(tmp);
    ID_SCORE_VEC result = cf.recommended_items_for_user("0", "item-based", -1,
                                                        0.5, 10, false);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0].first, "6");
    EXPECT_NEAR(result[0].second, 6.38621, 1e-5);

    EXPECT_EQ(result[1].first, "4");
    EXPECT_NEAR(result[1].second, 5.67794, 1e-5);

    EXPECT_EQ(result[2].first, "2");
    EXPECT_NEAR(result[2].second, 2.38576, 1e-5);
}

TEST(CFTest, recommended_users_for_item_item_based) {
    auto tmp = InputReader(make_matrix<SP_COL>());
    CF cf(tmp);
    ID_SCORE_VEC result = cf.recommended_users_for_item("0", "item-based", 3, 0.5, 10, false);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0].first, "1");
    EXPECT_NEAR(result[0].second, 7.37131, 1e-5);

    EXPECT_EQ(result[1].first, "5");
    EXPECT_NEAR(result[1].second, 7.30094, 1e-5);

    EXPECT_EQ(result[2].first, "6");
    EXPECT_NEAR(result[2].second, 6.59696, 1e-5);
}

TEST(CFTest, recommended_users_for_item_user_based) {
    auto tmp = InputReader(make_matrix<SP_COL>());
    CF cf(tmp);
    ID_SCORE_VEC result = cf.recommended_users_for_item("0", "user-based", -1, 0.5);
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0].first, "1");
    EXPECT_NEAR(result[0].second, 8.11169, 1e-5);

    EXPECT_EQ(result[1].first, "6");
    EXPECT_NEAR(result[1].second, 7.35234, 1e-5);

    EXPECT_EQ(result[2].first, "5");
    EXPECT_NEAR(result[2].second, 6.97994, 1e-5);
}
