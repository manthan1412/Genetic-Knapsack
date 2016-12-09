import random
from sys import stdout
import numpy

b_range = 1000
v_range = 50


def generate_knapsack(total):
    benefits = []
    volume = []
    for i in range(0, total):
        benefits.append(random.randint(1, b_range))
        volume.append(random.randint(1, v_range))
    return [benefits, volume]

fitting = []
chromosomes = []
unique = {}


def print_knapsack(n):
    for i in range(0, n):
        stdout.write("%5d" % i)
    stdout.write("\n")
    for i in range(0, n):
        stdout.write("%5d" % benefits[i])
    stdout.write("\n")
    for i in range(0, n):
        stdout.write("%5d" % volume[i])
    stdout.write("\n")


def to_binary(number, l):
    temp = ""
    j = 0
    while number != 0:
        temp += str(number % 2)
        number /= 2
        j += 1

    for i in range(j, l):
        temp += "0"

    return temp[::-1]


def not_unique(s):
    s = str(s)
    try:
        t = unique[s]
        return True
    except:
        return False


def generate_chromosomes():
    l = len(volume)
    for i in range(0, l):
        s = random.randint(1, 2**l-1)
        while not_unique(s):
            s = random.randint(1, 2**l-1)
        item = str(s)
        unique[item] = 1
        sbin = to_binary(s, l)
        # print s, sbin_temp
        chromosomes.append(sbin)
        fitting.append(s)


def calculate(chromosome):
    l = len(chromosome)
    total_weight = 0
    total_benefits = 0
    for i in range(0, l):
        if chromosome[i] == '1':
            total_benefits += benefits[i]
            total_weight += volume[i]
    return [total_benefits, total_weight]


def not_selected(chromosome, item):
    if chromosome[item] == "0":
        return True
    return False


def fitness(chromosomes):
    l = len(chromosomes)
    for i in range(0, l):
        knapsackv = calculate(chromosomes[i])
        while knapsackv[1] > knapsack_capacity:
            item = random.randint(0, total_items - 1)
            # print item
            while not_selected(chromosomes[i], item):
                item = random.randint(1, total_items - 1)
                print item
            new = ""
            if item == 0:
                new = "0" + chromosomes[i][1:]
            elif item == total_items - 1:
                new = chromosomes[i][:item] + "0"
            else:
                new = chromosomes[i][:item] + "0" + chromosomes[i][item+1:]
            chromosomes[i] = new
            knapsackv = calculate(chromosomes[i])


def roulette_selection():
    r = random.randint(0, volume_sum - 1)

    for i in range(0, total_items):
        r -= volume[i]
        if r <= 0:
            return i


def select(chromosomes):
    n1 = roulette_selection()
    n2 = n1
    while n2 == n1:
        n2 = roulette_selection()

    c = [chromosomes[n1], chromosomes[n2]]
    indices = [n1, n2]
    return [indices, c]


def crossover(selected):
    parent1 = selected[0]
    parent2 = selected[1]
    crossover_point = random.randint(0, total_items - 1)

    p = numpy.random.binomial(1, crossover_rate)
    if p:
        child1 = parent1[:crossover_point + 1] + parent2[crossover_point + 1:]
        child2 = parent2[:crossover_point + 1] + parent1[crossover_point + 1:]
    else:
        child1 = parent1
        child2 = parent2

    # new1 = ""
    # new2 = ""
    # for i in range(0, total_items - 1):
    #     p = numpy.random.binomial(1, 0.95)
    #     if p:
    #         new1 += child1[i]
    #         new2 += child2[i]
    #     else:
    #         new1 += parent1[i]
    #         new2 += parent2[i]
    return [child1, child2]


def negate(item):
    if item == "0":
        return "1"
    return "0"


def mutation(selected):

    chromosome1 = selected[0]
    chromosome2 = selected[1]
    # print chromosome1, chromosome2

    new1 = ""
    new2 = ""
    for i in range(0, total_items - 1):
        p = numpy.random.binomial(1, mutation_rate)
        if p:
            if i == 0: 
                new1 = negate(chromosome1[0]) + chromosome1[1:]
                new2 = negate(chromosome2[0]) + chromosome2[1:]
            elif i == total_items - 1:
                new1 = chromosome1[: i] + negate(chromosome1[-1])
                new2 = chromosome2[: i] + negate(chromosome2[-1])
            else:
                new1 = chromosome1[0: i] + negate(chromosome1[i]) + chromosome1[i + 1:]
                new2 = chromosome2[0: i] + negate(chromosome2[i]) + chromosome2[i + 1:]

    return [new1, new2]


print "Number of items : "
total_items = int(raw_input())
print "Enter capacity : "
knapsack_capacity = int(raw_input())

[benefits, volume] = generate_knapsack(total_items)
volume_sum = 0
for i in range(0, total_items):
    volume_sum += volume[i]

print_knapsack(total_items)
generate_chromosomes()

limit = 5
generation = 0
crossover_rate = 0.95
mutation_rate = 0.05
while generation <= limit:
    fitness(chromosomes)
    [indices, selected] = select(chromosomes)
    result = crossover(selected)
    print result, indices
    result = mutation(result)
    chromosomes[indices[0]] = result[0]
    chromosomes[indices[1]] = result[1]

    generation += 1
