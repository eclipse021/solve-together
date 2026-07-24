def solution(n, info):
    final_result = [-1]
    result = [0,0,0,0,0,0,0,0,0,0,0]
    max_sum = 0

    def dfs(arrow, start):
        nonlocal max_sum, final_result # 바깥의 변수를 갱신하기 위해 선언

        # 1. 종료 조건: 화살을 다 썼거나, 끝(0점 과녁)까지 탐색을 마쳤을 때
        if arrow == n or start == 11:
            # 남은 화살이 있다면 모두 가장 낮은 점수인 0점(인덱스 10)에 몰아주기
            leftover = n - arrow
            result[10] += leftover

            # 둘 점수 계산하는데 동점이면 어피치가 가져가는 조건 잊지마
            ryan_score = 0
            apeach_score = 0
            for i in range(11):
                if info[i] == 0 and result[i] == 0:
                    continue
                if result[i] > info[i]:
                    ryan_score += 10 - i
                else:
                    apeach_score += 10 - i

            temp_sum = ryan_score - apeach_score

            if temp_sum > 0:
                if temp_sum > max_sum:
                    max_sum = temp_sum
                    # 그냥 = result 하면 참조가 되니까 얕은 복사를 하든 이거를 하든 하자
                    final_result = [score for score in result]
                elif temp_sum == max_sum:
                    # 조건에서 점수 차 같으면 뒤부터 비교하면서 낮은 수 있나 보기
                    for i in range(10, -1, -1):
                        if result[i] > final_result[i]:
                            final_result = [score for score in result]
                            break
                        elif result[i] < final_result[i]:
                            break
            # 백트래킹: 남은 화살을 0점에 몰아줬던 것을 원상복구 (다음 탐색을 위해)
            result[10] -= leftover
            return
        
        # 2. 탐색 분기: 이번 과녁(start)에서 어피치를 이길 수 있다면 화살 쏘기
        # for문을 써서 탐색할 수도 있지만 이 문제는 점수를 딴다 못딴다 2개로만 나뉘어서 OX 퀴즈처럼 순서대로 넘어감
        narrow = arrow + (info[start] + 1)
        if narrow <= n:
            result[start] = info[start] + 1 
            dfs(narrow, start + 1)          # 다음 과녁으로 이동
            result[start] = 0               # 백트래킹 (원상복구)

        # 3. 탐색 분기: 이번 과녁(start)을 포기하고 안 쏘고 넘어가기
        dfs(arrow, start + 1)

    dfs(0, 0)

    return final_result