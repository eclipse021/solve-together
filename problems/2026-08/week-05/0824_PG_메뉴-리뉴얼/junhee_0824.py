from collections import Counter
from itertools import combinations


def solution(orders, course):
    answer = []

    for c in course:
        all_comb = []
        for o in orders:
            for comb in combinations(sorted(o), c):
                all_comb.append("".join(comb))
        counts = Counter(all_comb).most_common()

        if counts and counts[0][1] >= 2:
            answer.append(counts[0][0])

            for i in range(1, len(counts)):
                if counts[i][1] == counts[i-1][1]:
                    answer.append(counts[i][0])
                else:
                    break
    answer.sort()
    
    return answer