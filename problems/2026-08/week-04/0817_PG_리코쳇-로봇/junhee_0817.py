from collections import deque


def solution(board):
    # 북 동 남 서 
    dr, dc = [-1, 0, 1, 0], [0, 1, 0, -1]
    N, M = len(board), len(board[0])
    visited = [[False] * M for _ in range(N)]
    q = deque()

    for i in range(N):
        for j in range(M):
            if board[i][j] == 'R':
                visited[i][j] = True
                q.append((i, j, 0))
                break
    while q:
        r, c, count = q.popleft()
        if board[r][c] == 'G':
            return count

        for d in range(4):
            nr, nc = r + dr[d], c + dc[d]
            while 0 <= nr < N and 0 <= nc < M and board[nr][nc] != 'D':
                nr += dr[d]
                nc += dc[d]

            nr -= dr[d]
            nc -= dc[d]

            if not visited[nr][nc]:
                visited[nr][nc] = True
                q.append((nr, nc, count + 1))

    return -1