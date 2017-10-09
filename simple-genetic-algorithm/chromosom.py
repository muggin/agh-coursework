#!/usr/bin/python

import random

class Chromosom(object):
    '''Class Chromosom'''
    __genotype_size__ = 32

    def __init__(self):
        self.fitness = 0
        self.genotype = []

    def __cmp__(self, other):
        assert isinstance(other, Chromosom)
        return cmp(self.fitness, other.fitness)

    def random_init(self):
        self.genotype = [random.randint(0, 1) for x in xrange(self.__genotype_size__)]
        return self.genotype

    def count_fitness(self):
        self.fitness = sum(self.genotype)
        return self.fitness
