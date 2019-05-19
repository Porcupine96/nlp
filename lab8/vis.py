import matplotlib.pyplot as plt


def plot_score(metric, metrics, kernel, ax=None):
    metrics = \
        metrics \
        .where(metrics['kernel'] == kernel) \
        .groupby(by=metric).max()

    return metrics \
            .reset_index() \
            .plot(x=metric, y='score', logx=True, legend=False, ax=ax)


def plot_metrics_for(metrics):
    ncols = 3
    fig, axes = plt.subplots(ncols=ncols)
    fig.set_size_inches((4.5 * ncols, 4))

    ms = ['C', 'tol', 'drop_threshold']

    for m, ax in zip(ms, axes):
        plot_score(m, metrics, 'rbf', ax)
        ax.set_title(m)

    plt.show()
