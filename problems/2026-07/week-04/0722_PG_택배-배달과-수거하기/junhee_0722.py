# 그리디와 기본적 배열형 누적합이 아닌 변수 하나에 값을 계속 누적하며 상태를 갱신하는 변수형 누적으로 푸는 문제
def solution(cap, n, deliveries, pickups):
    answer = 0
    del_sum, pick_sum = 0, 0  
   
    for i in range(n - 1, -1, -1):
        del_sum += deliveries[i]
        pick_sum += pickups[i]
        
        # 둘 중 하나라도 배달/수거할 것이 있다면 그 집을 방문
        while del_sum > 0 or pick_sum > 0:
            del_sum -= cap  # 트럭 용량만큼 배달
            pick_sum -= cap # 트럭 용량만큼 수거
            answer += (i + 1) * 2 # 왕복 거리 더하기
            
    return answer