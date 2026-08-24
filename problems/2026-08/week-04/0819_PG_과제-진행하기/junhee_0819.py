from collections import deque

def time_to_minutes(t):
    hour, min = map(int, t.split(":"))
    return 60 * hour + min

def solution(plans):
    answer = []
    stack = deque()
    
    for plan in plans:
        plan[1] = time_to_minutes(plan[1])
        plan[2] = int(plan[2])

    plans.sort(key=lambda x: x[1])

    for i in range(len(plans)):
        name, start, playtime = plans[i]
    
        if i < len(plans) - 1:
            next_start = plans[i+1][1]
            time_diff = next_start - start  
            
            if playtime <= time_diff:
                answer.append(name)
                time_diff -= playtime  # 과제를 끝내고 남은 여유 시간 갱신
                
                # 남은 여유 시간 동안 스택에 멈춰둔 과제들 처리 
                while stack and time_diff > 0:
                    if stack[-1][1] <= time_diff:
                        time_diff -= stack[-1][1]
                        answer.append(stack.pop()[0])
                    else:
                        stack[-1][1] -= time_diff
                        break 
                        
            else:
                stack.append([name, playtime - time_diff])
                
        else:
            answer.append(name) 
            while stack:
                answer.append(stack.pop()[0])

    return answer