from chromosom import Chromosom
import random

class SGA(object):

    def __init__(self, generation_count = 100, population_size = 50, mutation_probability = 0.1, crossover_probability = 0.9):
        self.generation_count = generation_count
        self.population_size = population_size
        self.population = []
        self.new_population = []
        self.best_in_generations = []
        self.mutation_probability = mutation_probability
        self.crossover_probability = crossover_probability
        self.__total_fitness__ = 0

    def restart_algorithm(self):
        self.population = []
        self.new_population = []
        self.best_in_generations = []
        self.__total_fitness__ = 0


    def init_population(self):
        self.population = [Chromosom() for x in range(self.population_size)]
        for individual in self.population:
            individual.random_init()
            self.__total_fitness__ += individual.count_fitness()
        return 0

    def generate_new_population(self):
        for index in xrange(0, self.population_size / 2):
            parent_a = self.selection_operator()
            parent_b = self.selection_operator()

            if self.crossover_probability > random.uniform(0, 1):
                [child_a, child_b] = self.crossover_operator(parent_a, parent_b)
            else:
                child_a = self.mutation_operator(parent_a)
                child_b = self.mutation_operator(parent_b)

            self.new_population.append(child_a)
            self.new_population.append(child_b)
        return 0

    def evaluate_new_population(self):
        self.__total_fitness__ = 0
        for individual in self.new_population:
            self.__total_fitness__ += individual.count_fitness()
        self.new_population.sort(reverse=True)
        return 0

    def replace_population(self):
        self.population = self.new_population
        self.new_population = []

    def selection_operator(self):
        random_probability = random.uniform(0, 1)
        accumulated_fitness = 0.0

        for individual in self.population:
            accumulated_fitness += individual.fitness
            if(accumulated_fitness / self.__total_fitness__) >= random_probability:
                return individual

    def mutation_operator(self, chromosom_a):
        mutation_point = random.randint(0, len(chromosom_a.genotype) - 1)
        chromosom_a.genotype[mutation_point] = (chromosom_a.genotype[mutation_point] + 1) % 2
        return chromosom_a

    def crossover_operator(self, chromosom_a, chromosom_b):
        crossover_point = random.randint(0, len(chromosom_a.genotype) - 2) + 1
        child_a = Chromosom()
        child_b = Chromosom()

        for index in xrange(0, crossover_point):
            child_a.genotype.append(chromosom_a.genotype[index])
            child_b.genotype.append(chromosom_b.genotype[index])

        for index in xrange(crossover_point, len(chromosom_a.genotype)):
            child_a.genotype.append(chromosom_b.genotype[index])
            child_b.genotype.append(chromosom_a.genotype[index])
        return [child_a, child_b]

    def run_algorithm(self):
        self.init_population()
        for generation in xrange(0, self.generation_count):
            self.best_in_generations.append(self.population[0].fitness)
            self.generate_new_population()
            self.evaluate_new_population()
            self.replace_population()
        return self.best_in_generations



results = [0 for x in xrange(50)]
a = SGA()
for x in xrange(30):
    result = a.run_algorithm()
    print max(result)
    results = [x + y for x,y in zip(results, result)]
    a.restart_algorithm()

results = [x / 30.0 for x in results]

for x in xrange(len(results)):
    print 'Generation #%d - best individuals avg: %f' % (x, results[x])
