from collections import deque


T = int(input())
for count in range(1, T+1):
    N, K = map(int, input().split())
    all_num, one_side = [], N // 4
    q = deque(input())
    for i in range(one_side):
        for j in range(0, N, one_side):
            q_list = list(q)
            all_num.append("".join(q_list[j:j+one_side]))
        temp = q.pop()
        q.appendleft(temp)
    all_num = list(set(all_num))
    all_num.sort(reverse=True)
    num = int(all_num[K-1], 16)
    print(f"#{count} {num}")