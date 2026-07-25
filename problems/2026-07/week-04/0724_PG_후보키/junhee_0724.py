from itertools import combinations


def solution(relation):
    row_len = len(relation)      # 행의 개수 (유일성 검사할 때 필요)
    col_len = len(relation[0])   # 열의 개수 (조합 만들 때 필요)

    all_comb = []
    # 1. 컬럼 '인덱스'를 가지고 조합을 만듭니다. (0, 1, 2 ... col_len-1)
    for i in range(1, col_len + 1):
        # extend는 내용물만 들어감
        all_comb.extend(combinations(range(col_len), i))

    candidate = []
    for comb in all_comb:
        current_set = set(comb)
        is_minimal = True

        for key in candidate:
            # key가 current_set의 부분집합인지 확인이 issubset 함수
            if key.issubset(current_set):
                is_minimal = False
                break
        if is_minimal:
            unique_set = set(tuple(row[idx] for idx in comb) for row in relation)
            if len(unique_set) == row_len:
                candidate.append(current_set)

    return len(candidate)