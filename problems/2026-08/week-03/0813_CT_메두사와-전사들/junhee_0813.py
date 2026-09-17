from collections import deque

# N x N 마을 크기, 전사의 수 M
N, M = map(int, input().split())
# 메두사 집 sr, sc 와 공원 위치 er, ec
sr, sc, er, ec = map(int, input().split())
# M명의 전사들의 좌표 
temp = list(map(int, input().split()))
warriors = []
for i in range(0, 2*M, 2):
    warriors.append((temp[i], temp[i+1]))
    
# 마을 
grid = [list(map(int, input().split())) for _ in range(N)]

# 상 하 좌 우
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]
# 좌 우 상 하
dr2 = [0, 0, -1, 1]
dc2 = [-1, 1, 0, 0]

# [해설지 적용 1] 시야 방향(상,하,좌,우)에 따른 3갈래 빛 배열
VISION_DXYS = [
    [(-1, -1), (-1, 0), (-1, 1)],  # 0: 상
    [(1, -1), (1, 0), (1, 1)],     # 1: 하
    [(-1, -1), (0, -1), (1, -1)],  # 2: 좌
    [(-1, 1), (0, 1), (1, 1)],     # 3: 우
]

# [해설지 적용 2] 도착점(er, ec)에서부터의 거리를 잰 후, 우선순위에 맞게 경로 생성
def medusa_move(sr, sc):
    dist = [[-1] * N for _ in range(N)]
    q = deque()
    q.append((er, ec))
    dist[er][ec] = 0
    
    # 공원에서 집으로 퍼져나가는 BFS (거리 기록)
    while q:
        r, c = q.popleft()
        for d in range(4):
            nr, nc = r + dr[d], c + dc[d]
            if 0 <= nr < N and 0 <= nc < N and grid[nr][nc] == 0 and dist[nr][nc] == -1:
                dist[nr][nc] = dist[r][c] + 1
                q.append((nr, nc))
                
    # 경로가 없다면
    if dist[sr][sc] == -1:
        return []
        
    # 집에서부터 공원 방향으로 거리가 줄어드는 쪽(우선순위 상하좌우)으로 추적!
    path = []
    curr_r, curr_c = sr, sc
    while (curr_r, curr_c) != (er, ec):
        for d in range(4):
            nr, nc = curr_r + dr[d], curr_c + dc[d]
            if 0 <= nr < N and 0 <= nc < N and dist[nr][nc] != -1:
                # 거리가 딱 1 줄어드는 곳이 최단경로의 다음 스텝!
                if dist[nr][nc] == dist[curr_r][curr_c] - 1:
                    path.append((nr, nc))
                    curr_r, curr_c = nr, nc
                    break # 상하좌우 우선순위를 지켰으니 즉시 break
    return path

# [해설지 적용 3] 기존의 수학 공식을 버리고, 3갈래 빛 BFS로 시야/그림자를 한 번에 구함
def get_vision_info(mr, mc, d, warriors):
    vision = [[False] * N for _ in range(N)]
    warrior_positions = set((r, c) for r, c in warriors) # 빠른 검색을 위해 set으로
    
    dxys3 = VISION_DXYS[d]
    vis_q = deque() # 그림자를 계산할 빛의 파편들
    q = deque([(mr, mc)])
    
    # 1. 3갈래로 시야 퍼뜨리기
    while q:
        r, c = q.popleft()
        for dxi, dyi in dxys3: # 3갈래(좌대각, 직진, 우대각)로 뻗어감
            nr, nc = r + dxi, c + dyi
            if 0 <= nr < N and 0 <= nc < N and not vision[nr][nc]:
                # 전사를 만났다면 빛의 종류(t)를 기록해서 그림자 대기열(vis_q)에 넣음!
                if (nr, nc) in warrior_positions:
                    if nr == mr or nc == mc:
                        vis_q.append((nr, nc, 1)) # 정면(직진) 빛을 맞음
                    else:
                        t = 0 if (nr - mr) * dxys3[0][0] > 0 and (nc - mc) * dxys3[0][1] > 0 else 2
                        vis_q.append((nr, nc, t)) # 좌/우 대각선 빛을 맞음
                
                vision[nr][nc] = True # 일단 무조건 시야를 밝힘(True)
                q.append((nr, nc))
                
    # 2. 전사에 막힌 빛 뒤쪽(그림자) 지우기
    while vis_q:
        r, c, t = vis_q.popleft()
        for idx, (dxi, dyi) in enumerate(dxys3):
            if t == 1 and idx != 1: continue # 직진은 직진만 가림
            if t == 0 and idx == 2: continue # 좌대각은 우대각 못가림
            if t == 2 and idx == 0: continue # 우대각은 좌대각 못가림
            
            nr, nc = r + dxi, c + dyi
            if 0 <= nr < N and 0 <= nc < N and vision[nr][nc]:
                vision[nr][nc] = False # 그림자니까 시야에서 지움
                vis_q.append((nr, nc, t))
                
    # 완성된 맵 위에 있는 전사들만 수집
    visible_warriors = []
    for wr, wc in warriors:
        if vision[wr][wc]:
            visible_warriors.append((wr, wc))
            
    # 돌이 될 전사 리스트와, 완성된 시야 맵을 한 번에 리턴
    return visible_warriors, vision

# [이 함수는 작성하신 그대로 100% 유지!]
def move_all_warriors(mr, mc, warriors, choose_warriors, is_sight):
    next_warriors = []
    move_distance = 0 
    attack_count = 0  
    
    for wr, wc in warriors:
        if (wr, wc) in choose_warriors:
            next_warriors.append((wr, wc))
            continue
            
        dist1 = abs(mr - wr) + abs(mc - wc)
        next_r1, next_c1 = wr, wc
        for d in range(4):
            nr, nc = wr + dr[d], wc + dc[d]
            if 0 <= nr < N and 0 <= nc < N and not is_sight[nr][nc]:
                if abs(mr - nr) + abs(mc - nc) < dist1:
                    next_r1, next_c1 = nr, nc
                    move_distance += 1 
                    break
        
        dist2 = abs(mr - next_r1) + abs(mc - next_c1)
        next_r2, next_c2 = next_r1, next_c1
        for d in range(4):
            nr, nc = next_r1 + dr2[d], next_c1 + dc2[d]
            if 0 <= nr < N and 0 <= nc < N and not is_sight[nr][nc]:
                if abs(mr - nr) + abs(mc - nc) < dist2:
                    next_r2, next_c2 = nr, nc
                    move_distance += 1 
                    break
                    
        if (next_r2, next_c2) == (mr, mc):
            attack_count += 1
        else:
            next_warriors.append((next_r2, next_c2))
            
    return next_warriors, move_distance, attack_count

# --- [작성하신 메인 루프 구조 그대로 유지] ---
medusa_path = medusa_move(sr, sc)

if medusa_path:
    # 작성하신 for문 로직 완벽히 동일하게 활용
    for mr, mc in medusa_path:
        if (mr, mc) == (er, ec):
            print(0)
            break
            
        survived_warriors = []
        for wr, wc in warriors:
            if (wr, wc) != (mr, mc):
                survived_warriors.append((wr, wc))
        warriors = survived_warriors
        
        if not warriors:
            print("0 0 0")
            continue

        real_visible = []
        for d in range(4):
            # [유일하게 수정된 호출부] 4방향을 돌며 시야맵과 전사를 동시에 받아옴
            visible, vision_map = get_vision_info(mr, mc, d, warriors)
            real_visible.append((visible, vision_map, d))
            
        # 돌이 된 수 내림차순, 방향 우선순위(d가 상하좌우 순) 오름차순
        real_visible.sort(key=lambda x: (-len(x[0]), x[2]))
        
        # 1등으로 뽑힌 값들을 내 원래 변수에 그대로 할당!
        choose_warriors = real_visible[0][0]
        is_sight = real_visible[0][1] 
        # choose_direction = real_visible[0][2] (이제 쓸 필요가 없어짐)

        # 3. 작성하신 함수 그대로 호출
        warriors, move_dist, attack_cnt = move_all_warriors(mr, mc, warriors, choose_warriors, is_sight)
        
        # 4. 결과 출력
        print(f"{move_dist} {len(choose_warriors)} {attack_cnt}")
else:
    print(-1)