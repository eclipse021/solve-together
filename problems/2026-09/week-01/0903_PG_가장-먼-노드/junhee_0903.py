from collections import deque


def solution(n, edge):
    graph = [[] for _ in range(n + 1)]
    for a, b in edge:
        graph[a].append(b)
        graph[b].append(a)
        
    q = deque([1])
    distance = [-1] * (n+1)
    distance[1] = 0
    
    while q:
        now = q.popleft()
        
        for nd in graph[now]:
            if distance[nd] == -1:
                distance[nd] = distance[now] + 1
                q.append(nd)
                
    max_dist = max(distance)
    
    return distance.count(max_dist)