import numpy as np


def uniform_binary_distortion(image, amount=0.2):
    # image size details
    rows, cols = image.shape
    index_vector_size = rows * cols

    # number of pixels to distort
    mutated_count = __clip_to_int_in_range(amount * index_vector_size, 0, index_vector_size)

    # draw pixels to distort (uniform on entire image)
    matrix_indices = __matrix_indices(rows, cols)
    mutated_indices = __draw_random_elements(matrix_indices, mutated_count)

    # distort pixels
    return __flip_binary_bits(image, mutated_indices)


def local_binary_distortion(image, amount=0.2):
    # image size details
    rows, cols = image.shape
    index_vector_size = rows * cols

    # number of pixels to distort
    mutated_count = __clip_to_int_in_range(amount * index_vector_size, 0, index_vector_size)

    # draw pixels to distort (locally from center)
    matrix_indices = __matrix_indices(rows, cols)
    random_index = np.random.randint(0, index_vector_size-1)
    mutation_center = matrix_indices[random_index]

    neighbor_list = [mutation_center]
    mutated_indices = []

    while not neighbor_list or (len(mutated_indices) < mutated_count):
        next_index = neighbor_list.pop(0)
        mutated_indices.append(next_index)

        for (x, y) in [(-1, 0), (0, -1), (1, 0), (0, 1)]:
            if (0 <= next_index[0]+x < rows) and (0 <= next_index[1]+y < cols) and ((next_index[0]+x, next_index[1]+y) not in mutated_indices):
                    neighbor_list.append((next_index[0]+x, next_index[1]+y))
    return __flip_binary_bits(image, mutated_indices)


def __clip_to_int_in_range(value, lower, upper):
    '''
    '''
    return int(max(lower, min(upper, value)))


def __matrix_indices(rows, cols):
    '''
    '''
    return [(x, y) for x in xrange(0, rows) for y in xrange(0, cols)]


def __draw_random_elements(vector, count):
    '''
    '''
    np.random.shuffle(vector)
    return vector[:count]


def __flip_binary_bits(image, indices):
    for (row, col) in indices:
        image[row, col] ^= 1
    return image
