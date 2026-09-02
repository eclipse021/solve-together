def solution(stones, k):
    answer = 0
    left, right = 1, 200000000 
    
    while left <= right:
        is_cross = True
        skip = 0
        mid = (left + right) // 2
        
        for s in stones:
            if s < mid:
                skip += 1
            else:
                skip = 0
            if skip == k:
                is_cross = False
                break
                
        if is_cross:
            answer = mid
            left = mid + 1
        else:
            right = mid - 1
        
    return answer