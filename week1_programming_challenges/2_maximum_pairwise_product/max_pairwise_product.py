# python3


def max_pairwise_product(numbers):
    n = len(numbers)
    max_product = 0
    for first in range(n):
        for second in range(first + 1, n):
            max_product = max(max_product,
                numbers[first] * numbers[second])

    return max_product


def better_max(numbers):
    n = len(numbers)
    m1 = max(numbers)
    ind = []
    for i in range(n):
        if numbers[i] == m1:
            ind.append(i)
    
    for i in range(n):
        
            
            
if __name__ == '__main__':
    input_n = int(input())
    input_numbers = [int(x) for x in input().split()]
    print(max_pairwise_product(input_numbers))
