def dfs(depth, total):
    global max_sum, min_sum
    if depth == N - 1:
        max_sum = max(max_sum, total)
        min_sum = min(min_sum, total)
        return
    
    for i in range(4):
        if operators[i] > 0:
            operators[i] -= 1
            if i == 0:
                dfs(depth + 1, total + numbers[depth + 1])
            elif i == 1:
                dfs(depth + 1, total - numbers[depth + 1])
            elif i == 2:
                dfs(depth + 1, total * numbers[depth + 1])
            elif i == 3:
                dfs(depth + 1, int(total / numbers[depth + 1]))
                
            operators[i] += 1


T = int(input())
for i in range(1, T+1):
    N = int(input())
    operators = list(map(int, input().split()))
    numbers = list(map(int, input().split()))
    max_sum, min_sum = -float('inf'), float('inf')
    dfs(0, numbers[0])
    print(f"#{i} {max_sum - min_sum}")