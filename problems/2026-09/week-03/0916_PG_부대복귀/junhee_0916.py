from collections import deque


def solution(n, roads, sources, destination):
    answer = []

    g = [[] for _ in range(n+1)]
    for road in roads:
        a, b = road[0], road[1]
        g[a].append(b)
        g[b].append(a)

    q = deque([destination])
    dist = [-1] * (n + 1)
    dist[destination] = 0

    while q:
        r = q.popleft()

        for nr in g[r]:
            if dist[nr] == -1:
                dist[nr] = dist[r] + 1
                q.append(nr)

    for s in sources:
        answer.append(dist[s])

    return answer