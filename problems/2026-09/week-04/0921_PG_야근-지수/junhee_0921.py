import heapq


def solution(n, works):
    answer = 0
    heap = []

    for work in works:
        heapq.heappush(heap, -work)

    for _ in range(n):
        temp = heapq.heappop(heap)
        temp += 1

        if temp < 0:
            heapq.heappush(heap, temp)
        else:
            heapq.heappush(heap, 0)

    for h in heap:
        answer += h**2

    return answer