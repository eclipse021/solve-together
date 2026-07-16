from collections import deque


def solution(queue1, queue2):
    q1, q2 = deque(queue1), deque(queue2)
    count, is_same = 0, False
    sum_q1, sum_q2 = sum(q1), sum(q2)
    
    for i in range(len(q1)*3):
        if sum_q1 > sum_q2:
            tmp = q1.popleft()
            q2.append(tmp)
            sum_q1, sum_q2 = sum_q1 - tmp, sum_q2 + tmp
            count += 1
        elif sum_q1 < sum_q2:
            tmp = q2.popleft()
            q1.append(tmp)
            sum_q1, sum_q2 = sum_q1 + tmp, sum_q2 - tmp
            count += 1
        else:
            is_same = True
            break
    
    return count if is_same else -1