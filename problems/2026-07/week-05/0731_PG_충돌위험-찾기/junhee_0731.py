from collections import Counter


def solution(points, routes):
    answer = 0
    paths = [[] for _ in range(20000)]
    for route in routes:
        time = 0
        for i in range(len(route) - 1):
            start = points[route[i] - 1]
            end = points[route[i+1] - 1]
            # 얕은 복사 주의해라 반드시 (주소 복사 방지)
            temp = start[:]
            
            while temp != end:
                paths[time].append(tuple(temp))
               
                if temp[0] != end[0]:
                    if temp[0] > end[0]:
                        temp[0] -= 1
                    elif temp[0] < end[0]:
                        temp[0] += 1
                else:
                    if temp[1] > end[1]:
                        temp[1] -= 1
                    elif temp[1] < end[1]:
                        temp[1] += 1
                time += 1
        paths[time].append(tuple(temp))      
     
    for path in paths:
        path_counter = Counter(path)
        for key in path_counter:
            if path_counter[key] > 1:
                answer += 1
    return answer