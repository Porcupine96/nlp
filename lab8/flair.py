def teach_flair(train_path, validation_path):
    best_score = None
    best_classifier = None
    metrics = []

    for lr in [i / 10 for i in range(1, 40, 5)]:
        for wordNgrams in [1, 2, 3]:
            model = fastText.train_supervised(
                train_path, lr=lr, wordNgrams=wordNgrams)

            # TODO: instead of model.test use the method from sklearn
            (_, precision, recall) = model.test(validation_path)
            score = f1_score(precision, recall)

            if best_score is None or score > best_score:
                best_score = score
                best_classifier = model
                print('Score {0} for lr={1}, wordNgrams={2}'.format(
                    score, lr, wordNgrams))

            metrics.append((lr, score, wordNgrams))

    metric_df = pd.DataFrame(metrics, columns=['lr', 'score', 'wordNgrams'])

    return best_classifier, metrics
