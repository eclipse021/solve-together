import math

def solution(n, stations, w):
    answer = 0
    cover = 2 * w + 1
    current = 1  

    for s in stations:
        left = s - w

        if current < left:
            empty_length = left - current
            answer += math.ceil(empty_length / cover)  
            
        current = s + w + 1

    if current <= n:
        empty_length = n - current + 1
        answer += math.ceil(empty_length / cover)

    return answer