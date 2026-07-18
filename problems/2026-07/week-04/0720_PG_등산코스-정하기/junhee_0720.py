import heapq

def solution(n, paths, gates, summits):
    # 1. 그래프 만들기 (양방향 연결)
    graph = [[] for _ in range(n + 1)]
    for u, v, w in paths:
        graph[u].append((v, w))
        graph[v].append((u, w))
        
    # 산봉우리인지 빠르게 `O(1)`로 확인하기 위해 set으로 변환
    summits_set = set(summits)
    
    # 2. intensity(휴식 없이 이동하는 가장 긴 시간) 테이블 초기화
    # 일반 다익스트라의 distance 배열과 같은 역할입니다.
    intensity = [float('inf')] * (n + 1)
    
    # 3. 다중 출발점 세팅
    q = []
    for gate in gates:
        # TODO 1: 큐에 (초기 intensity, 출발지 노드 번호)를 넣고, 해당 출발지의 intensity 테이블 값을 0으로 갱신하세요.
        heapq.heappush(q, (0, gate))
        intensity[gate] = 0
        
    # 4. 탐색 시작
    while q:
        current_intensity, now = heapq.heappop(q)
        
        # TODO 2: 이미 처리된 노드라면 무시 (테이블의 값과 현재 꺼낸 값 비교)
        if intensity[now] < current_intensity:
            continue

        # TODO 3: 현재 노드(now)가 산봉우리(summits_set) 중 하나라면 더 나아가지 않음 (탐색 중단 후 다른 경로 확인)
        if now in summits_set:
            continue
        
        # 5. 인접 노드 탐색
        for next_node, weight in graph[now]:
            # TODO 4: 새로운 intensity 계산 (이 문제의 핵심!)
            # 현재까지 거쳐온 구간들의 최대 intensity와 이번 간선의 weight 중 더 큰 값이 새로운 intensity가 됩니다.
            new_intensity = max(intensity[now], weight)
            
            # TODO 5: 새로 구한 new_intensity가 기존 테이블에 기록된 next_node의 intensity보다 작다면?
            # 테이블을 갱신하고 큐에 (new_intensity, next_node)를 삽입하세요.
            if new_intensity < intensity[next_node]:
                intensity[next_node] = new_intensity
                heapq.heappush(q, (new_intensity, next_node))
            
    # 6. 정답 도출
    # 산봉우리 번호가 작은 것을 우선해야 하므로, summits를 미리 오름차순 정렬해 두면 편합니다.
    summits.sort()
    
    answer = [0, float('inf')]
    
    for summit in summits:
        # TODO 6: 기록된 intensity 테이블에서 현재 summit의 값이 answer의 최소 intensity보다 작다면 answer 갱신
        if intensity[summit] < answer[1]:
            answer[0], answer[1] = summit, intensity[summit] 
    
    return answer