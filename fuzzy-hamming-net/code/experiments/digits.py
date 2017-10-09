#! /usr/bin/python

import code.net.ham_net as hn
import code.examples.binary_digits as bd
import code.utils.helper_methods as um
import code.utils.plotting as plt

if __name__ == '__main__':
    hm = hn.HammingNet(bd.proper_digits)
    test_image1 = um.uniform_binary_distortion(bd.nine_proper, 0.0)
    winning_pattern1, b = hm.match(test_image1)
    print winning_pattern1
    print test_image1
    plt.add_figure(test_image1, winning_pattern1, b)

    # test_image2 = um.uniform_binary_distortion(bd.nine_proper, 0.4)
    # winning_pattern2, b = hm.match(test_image2)
    # plt.add_figure(test_image2, winning_pattern2, b)
    plt.show_experiments()
