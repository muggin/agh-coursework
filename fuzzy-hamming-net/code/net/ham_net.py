import numpy as np
import code.examples.binary_digits as bd
import code.utils.plotting as plt
import code.utils.helper_methods as um


def binary_to_bipolar(binary_vector):
    '''
    Transform binary vector to bipolar (-1;1) representation
    :param binary_vector: vector holding binary values
    :return: vector holding bipolar values
    '''
    bipolar_vector = [1 if element > 0 else -1 for element in binary_vector]
    return np.array(bipolar_vector)


def hamming_distance(vec_1, vec_2):
    '''
    Calculate the hamming distance between two vectors
    :param vec_1: first vector
    :param vec_2: second vector
    :return: hammming distance between input vectors.
    '''
    assert len(vec_1) == len(vec_2), 'Input vectors have different length'
    return sum(element1 != element2 for element1, element2 in zip(vec_1, vec_2))


def threshold_function(vector):
    '''
    Threshold given
    :param vector:
    :return:
    '''
    return vector.clip(0)


class HammingNet(object):

    def __init__(self, input_patterns, to_bipolar=True):
        '''

        :param input_patterns:
        :param make_bipolar:
        :return:
        '''
        self.__stored_pattern_count = len(input_patterns)
        self.__stored_pattern_shape = input_patterns[0].shape
        transformed_patterns = []
        for pattern in input_patterns:
            new_pattern = np.array(pattern).flatten()
            if to_bipolar:
                new_pattern = binary_to_bipolar(new_pattern)
            transformed_patterns.append(new_pattern)
        self.__stored_patterns = np.array(transformed_patterns)
        self.__maxnet_weights = self.__generate_equal_maxnet_weights()

    def __generate_random_maxnet_weights(self, symmetric=True):
        '''

        :return:
        '''
        min_value = 0.000001
        max_value = 1. / self.__stored_pattern_count
        rand_values = np.random.uniform(min_value, max_value, (self.__stored_pattern_count, self.__stored_pattern_count))
        if symmetric:
            w = - (rand_values + rand_values.T) / 2.
        for idx in xrange(0, self.__stored_pattern_count - 1):
            w[idx, idx] = 1
        return w

    def __generate_equal_maxnet_weights(self, value=None):
        if not value:
            min_value = 0.000001
            max_value = 1. / self.__stored_pattern_count
            value = np.random.uniform(min_value, max_value)

        matrix_dim = (self.__stored_pattern_count, self.__stored_pattern_count)
        w = - np.full(matrix_dim, value)
        for idx in xrange(0, self.__stored_pattern_count):
            w[idx, idx] = 1
        return w

    def __compute_similarities(self, input_pattern):
        '''

        :param input_pattern:
        :return:
        '''
        similarity_vector = np.inner(self.__stored_patterns, input_pattern) + self.__stored_pattern_count
        return similarity_vector

    def __run_maxnet(self, similarity_layer_output, max_iter=10, eps=0.01):
        '''

        :param initial_values:
        :param max_iter:
        :param eps:
        :return:
        '''
        neuron_state = np.array(similarity_layer_output) / float(self.__stored_pattern_count)
        for i in xrange(0, max_iter):
            inner_product = np.inner(self.__maxnet_weights, neuron_state)
            neuron_state = threshold_function(inner_product)
        return neuron_state.argmax()

    def match(self, input_pattern):
        '''

        :param input_pattern:
        :return:
        '''
        assert(input_pattern.shape == self.__stored_pattern_shape)

        input_vector = np.array(input_pattern).flatten()
        input_vector = binary_to_bipolar(input_vector)
        # print 'Input vector: ', input_vector
        similarity_vector = self.__compute_similarities(input_vector)
        print 'Similarity vector: ', similarity_vector
        max_idx = self.__run_maxnet(similarity_vector)
        print 'Max index: ', max_idx
        winning_pattern = self.__stored_patterns[max_idx]
        return winning_pattern.reshape(self.__stored_pattern_shape), similarity_vector


if __name__ == '__main__':
    hm = HammingNet(bd.proper_digits)
    test_image1 = um.uniform_binary_distortion(bd.nine_proper, 0.15)
    winning_pattern1, similarities = hm.match(test_image1)
    plt.add_figure(test_image1, winning_pattern1, similarities)
    plt.show_experiments()
