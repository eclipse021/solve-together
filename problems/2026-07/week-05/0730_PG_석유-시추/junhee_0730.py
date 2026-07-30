from collections import deque


def solution(land):
    N, M = len(land), len(land[0])
    # 북 동 남 서
    dr, dc = [-1, 0, 1, 0], [0, 1, 0, -1]
    visited = [[False] * M for _ in range(N)]
    q = deque()
    spaces = [0] * M

    for i in range(N):
        for j in range(M):
            if  not visited[i][j]:
                visited[i][j] = True
                if land[i][j] == 1:
                    space = [j]
                    visited[i][j] = True
                    q.append((i,j))

                    while q:
                        r, c = q.popleft()
                        for d in range(4):
                            nr, nc = r + dr[d], c + dc[d]
                            if 0 <= nr < N and 0 <= nc < M and not visited[nr][nc] and land[nr][nc] == 1:
                                space.append(nc)
                                visited[nr][nc] = True
                                q.append((nr, nc))
                    space_length = len(space)
                    space_set = list(set(space))
                    for k in space_set:
                        spaces[k] += space_length
    return max(spaces)