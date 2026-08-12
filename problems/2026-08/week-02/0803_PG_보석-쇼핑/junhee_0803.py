def solution(gems):
    len_gems = len(set(gems))
    gem_dict = {}
    end, min_term = 0, (0, 0, float('inf'))

    for start in range(len(gems)):
        while len(gem_dict) < len_gems and end < len(gems):
            gem_dict[gems[end]] = gem_dict.get(gems[end], 0) + 1
            end += 1
            
        if len(gem_dict) == len_gems:
            if end - start < min_term[2]:
                min_term = (start, end-1, end - start)
                
        if min_term[2] == len_gems:
            break
        
        gem_dict[gems[start]] -= 1
        if gem_dict[gems[start]] == 0:
            del gem_dict[gems[start]]
            
    return [min_term[0] + 1, min_term[1] + 1]