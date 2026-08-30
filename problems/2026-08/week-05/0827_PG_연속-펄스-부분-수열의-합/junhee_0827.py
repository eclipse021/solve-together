def solution(sequence):
    prefix_sum = [0]  
    current_sum = 0
    pulse = 1
    
    for num in sequence:
        current_sum += num * pulse
        prefix_sum.append(current_sum)
        # 어짜피 절대값 씌우면 되니 펄스 수열 하나만 해도 됌
        pulse *= -1  
        
    # 단 하나의 펄스 누적 합 배열에서 최댓값 - 최솟값 반환
    return max(prefix_sum) - min(prefix_sum)