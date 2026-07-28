import heapq

INF = float('inf')
T = int(input())
# 북 동 남 서
dr, dc = [-1, 0, 1, 0], [0, 1, 0, -1]

def dijkstra(g):
    # 일단 다익스트라는 무조건 거리 테이블 먼저 만들기
    distance = [[INF] * N for _ in range(N)] 
    # 가중치가 다양한 다익스트라 문제니까 deque 대신 heapq 사용 (우선순위 큐)
    # 큐에 들어가는 데이터 형태: (누적 비용, r, c)
    q = []
    heapq.heappush(q, (0, 0, 0))
    distance[0][0] = 0

    while q:
        dist, r, c = heapq.heappop(q)
        
        if r == N-1 and c == N-1:
            return dist

        if distance[r][c] < dist:
            continue
        
        for d in range(4):
            nr, nc = r + dr[d], c + dc[d]
            if 0 <= nr < N and 0 <= nc < N:
                ndist = dist + g[nr][nc]
                if ndist < distance[nr][nc]:
                    distance[nr][nc] = ndist
                    heapq.heappush(q, (ndist, nr, nc))

    

for i in range(1, T+1):
    N = int(input())
    grid = [list(map(int, input())) for _ in range(N)]
    temp = dijkstra(grid)
    print(f"#{i} {temp}")