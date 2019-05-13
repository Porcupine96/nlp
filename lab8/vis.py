import matplotlib.pyplot as plt


def plot_score(metric, metrics, kernel, ax=None):
    metrics = \
        metrics \
        .where(metrics['kernel'] == kernel) \
        .groupby(by=metric).max()

    return metrics \
            .reset_index() \
            .plot(x=metric, y='score', logx=True, legend=False, ax=ax)


def plot_metrics_for(metric,
                     metrics,
                     kernels=['linear', 'poly', 'sigmoid', 'rbf']):
    fig, axes = plt.subplots(ncols=len(kernels), sharey=True)
    fig.set_size_inches((4.5 * len(kernels), 4))

    for kernel, ax in zip(kernels, [axes]):
        plot_score(metric, metrics, kernel, ax)
        ax.set_title(kernel)

    plt.show()
