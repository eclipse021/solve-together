def solution(n, m, x, y, r, c, k):
    # 하, 좌, 우, 상 (사전 순)
    dr, dc = [1, 0, 0, -1], [0, -1, 1, 0]
    direction = ['d', 'l', 'r', 'u']
    start_r, start_c, end_r, end_c = x - 1, y - 1, r - 1, c - 1
    
    # 1. 시작 전 아예 불가능한 경우 거르기
    initial_dist = abs(start_r - end_r) + abs(start_c - end_c)
    if initial_dist > k or (k - initial_dist) % 2 != 0:
        return "impossible"
    
    answer = ""
    curr_r, curr_c = start_r, start_c
    
    # 2. k번 이동하면서 매 칸마다 가장 최선의 방향 딱 하나만 선택
    for i in range(k):
        for d in range(4):
            nr, nc = curr_r + dr[d], curr_c + dc[d]
            
            if 0 <= nr < n and 0 <= nc < m:
                remain_dist = k - (i + 1)
                shortest_dist = abs(nr - end_r) + abs(nc - end_c)
                
                # 가지치기 조건: 도달 가능하며, 홀짝이 맞을 때만 큐에 추가
                if shortest_dist <= remain_dist and (remain_dist - shortest_dist) % 2 == 0:
                    curr_r, curr_c = nr, nc
                    answer += direction[d]
                    break  
                    
    return answer