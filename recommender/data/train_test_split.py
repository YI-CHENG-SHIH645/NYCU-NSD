import os
import numpy as np
import pandas as pd

if __name__ == '__main__':
    rng = np.random.default_rng(42)
    data_dir = "Book_reviews/Book_reviews"
    book_rating_data_path = os.path.join(data_dir, "BX-Book-Ratings.csv")
    raw_ratings = pd.read_csv(book_rating_data_path, delimiter=';', header=0, encoding='ISO-8859-1')

    test_idx = sorted(
        rng.choice(len(raw_ratings),
                   int(len(raw_ratings)*0.1),
                   replace=False)
    )
    train_idx = raw_ratings.index[~raw_ratings.index.isin(test_idx)]
    raw_ratings.loc[train_idx].to_csv(os.path.join(data_dir, "BX-Book-Ratings-train.csv"),
                                      index=False,
                                      index_label=False,
                                      sep=";")
    raw_ratings.loc[test_idx].to_csv(os.path.join(data_dir, "BX-Book-Ratings-test.csv"),
                                     index=False,
                                     index_label=False,
                                     sep=";")
