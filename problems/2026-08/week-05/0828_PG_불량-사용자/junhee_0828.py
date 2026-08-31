from itertools import permutations


def solution(user_id, banned_id):
    answer = set()
    
    for p in permutations(user_id, len(banned_id)):
        is_same = True
        for i in range(len(p)):
            word_one = p[i]
            word_two = banned_id[i]

            if len(word_one) != len(word_two):
                is_same = False
                break

            for j in range(len(word_one)):
                if word_one[j] != word_two[j] and word_two[j] != '*':
                    is_same = False
                    break
        if is_same:
            answer.add(tuple(sorted(p)))

    return len(answer)