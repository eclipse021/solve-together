from collections import deque


def solution(x, y, n):
    q = deque()
    q.append((x, 0))

    # 방문한 숫자를 기록할 set 추가
    visited = set()
    visited.add(x)

    while q:
        now, count = q.popleft()
        if now == y:
            return count

        for i in range(3):
            next, next_count = now, count + 1
            if i == 0:
                next += n
            elif i == 1:
                next *= 2
            elif i == 2:
                next *= 3

            if next <= y and next not in visited:
                visited.add(next)
                q.append((next, next_count))
            
    return -1