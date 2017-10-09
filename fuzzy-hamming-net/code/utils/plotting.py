import matplotlib.pyplot as plt


def add_figure(input_pattern, winning_pattern, winning_probability=0.0, experiment_title=''):
    figure = plt.figure()
    plt.title('Experiment')
    plt.gray()

    # display input pattern
    plt.subplot(1, 2, 1)
    plt.title('Input pattern')
    plt.axis('off')
    plt.imshow(input_pattern, interpolation='nearest')

    # display output pattern
    plt.subplot(1, 2, 2)
    plt.title('Winning pattern')
    plt.axis('off')
    plt.imshow(winning_pattern, interpolation='nearest')


def show_experiments():
    plt.show()
