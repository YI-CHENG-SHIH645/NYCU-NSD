import pandas as pd
from surprise import KNNBasic

if __name__ == '__main__':
    book_rating = "data/Book_reviews/Book_reviews/BX-Book-Ratings.csv"
    raw_ratings = pd.read_csv(book_rating, delimiter=';', header=0)
    # test_idx = sorted(np.random.choice(len(raw_ratings), int(len(raw_ratings)*0.1), replace=False))
    # train_idx = raw_ratings.index[~raw_ratings.index.isin(test_idx)]
    # raw_ratings.loc[train_idx].to_csv("data/Book-Ratings-train.csv", index=False, index_label=False, sep=";")
    # raw_ratings.loc[test_idx].to_csv("data/Book-Ratings-test.csv", index=False, index_label=False, sep=";")
    print((raw_ratings[raw_ratings['User-ID'] == 8]["Book-Rating"]+1).mean())
