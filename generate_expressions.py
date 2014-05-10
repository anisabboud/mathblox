'''
Created on May 5, 2014

@author: Anis
'''

from itertools import combinations
from itertools import permutations
import pprint

operators = ['+', '-', '*', '/']
numbers = [str(i + 1) for i in range(6)]
N = 4  # How many numbers are in the solution?
EPSILON = 10e-4
pp = pprint.PrettyPrinter(indent=4)

# Patterns are: n o n o n o n (3 operators surrounded by 4 numbers)
# 6 options for parentheses. 4 numbers, choose 2 to surround them by parentheses. E.g., (n o n) o n o n

all_quizzes = {}

count = 0
for left_parenthesis, right_parenthesis in combinations(range(N), 2):
    for nums in permutations(numbers, N):
        for ops in permutations(operators, N - 1):
            expression = nums[0]
            for i in range(len(ops)):
                expression += ops[i] + nums[i + 1]
            # Insert the parentheses.
            part1 = expression[:left_parenthesis * 2]
            part2 = expression[left_parenthesis * 2:right_parenthesis * 2 + 1]
            part3 = expression[right_parenthesis * 2 + 1:]
            final_expression = part1 + '(' + part2 + ')' + part3
            result = None
            try:
                float_expression = ''.join([item + '.0' if item.isdigit() else item for item in final_expression])
                result = int(eval(float_expression))
            except ZeroDivisionError:
                continue
            if abs(result - round(result)) > EPSILON or result <= 0:
                continue
            count += 1
            #print count, nums, ops, left_parenthesis, right_parenthesis, final_expression, result
            
            sorted_nums = tuple(sorted([int(i) for i in nums]))
            if sorted_nums not in all_quizzes:
                all_quizzes[sorted_nums] = set()
            all_quizzes[sorted_nums].add(result)

# for nums, result_set in sorted(all_quizzes.items()):
#     print nums, sorted(result_set)
# print

number_of_number_sets = len(all_quizzes)
print '#define N %d  // How many numbers are used in each exercise.' % N
print '#define NUM_SETS %d\n' % number_of_number_sets
print 'int nums_sets[NUM_SETS][N] = {'
for nums_set in sorted(all_quizzes):
    print '\t{%s},' % (', '.join([str(i) for i in nums_set]))
print '};'

print 'int results[NUM_SETS][%d] = {' % max([len(result_set) for result_set in all_quizzes.values()])
for nums_set, result_set in sorted(all_quizzes.items()):
    print '\t{%s},' % (', '.join([str(i) for i in result_set]))
print '};'


print 'int results_count[NUM_SETS] = {'
for nums_set, result_set in sorted(all_quizzes.items()):
    print '\t%d,' % len(result_set)
print '};'