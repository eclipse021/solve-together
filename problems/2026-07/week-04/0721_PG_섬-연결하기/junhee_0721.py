# 1. 부모 노드를 찾는 함수 (Find)
def find_parent(parent, x):
    if parent[x] != x:
        parent[x] = find_parent(parent, parent[x])
    return parent[x]

# 2. 두 집합을 합치는 함수 (Union)
def union_parent(parent, a, b):
    a = find_parent(parent, a)
    b = find_parent(parent, b)
    # 순서 상관없는데 관례 상 작은 노드를 최상위 부모로 둠
    if a < b:
        parent[b] = a
    else:
        parent[a] = b

def solution(n, costs):
    answer = 0
    # 부모 테이블 초기화 (처음엔 자기 자신을 부모로)
    parent = [i for i in range(n)]
    
    # 간선 비용을 기준으로 오름차순 정렬
    costs.sort(key=lambda x: x[2])
    
    # 비용이 적은 간선부터 하나씩 확인
    for a, b, cost in costs:
        # 사이클이 발생하지 않는 경우에만 집합에 포함 (연결)
        if find_parent(parent, a) != find_parent(parent, b):
            union_parent(parent, a, b)
            answer += cost
            
    return answer