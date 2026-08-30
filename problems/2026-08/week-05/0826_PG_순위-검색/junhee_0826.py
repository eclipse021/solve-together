from bisect import bisect_left
from collections import defaultdict
from itertools import product


def solution(info, query):
    answer = []
    people = defaultdict(list)

    for i in info:
        person = i.split()
        spec = person[:-1]
        score = int(person[-1])
        cases = product([spec[0], '-'], [spec[1], '-'], [spec[2], '-'], [spec[3], '-'])

        for case in cases:
            key = "".join(case)
            people[key].append(score)

    for key in people:
        people[key].sort()

    for q in query:
        q = q.replace(" and ", "")
        q = q.split()
        target_key = "".join(q[:-1])
        target_score = int(q[-1])

        if target_key in people:
            scores = people[target_key]
            idx = bisect_left(scores, target_score)
            answer.append(len(scores) - idx)
        else:
            answer.append(0)
    
    return answer