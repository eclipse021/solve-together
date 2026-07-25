//
// Created by 임준현 on 26. 7. 25.
//

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<vector<string>> overall_relation;
vector<vector<int>> candidate_keys;

// 현재 조합이 기존 후보키를 포함하는지 검사
bool is_minimal(const vector<int>& index_list) {

    for (const vector<int>& candidate_key : candidate_keys) {

        // candidate_key가 index_list의 부분집합이면 최소성 위반
        if (includes(
                index_list.begin(),
                index_list.end(),
                candidate_key.begin(),
                candidate_key.end()
        )) {
            return false;
        }
    }

    return true;
}

// 유일성 검사
bool update(const vector<int>& index_list) {

    unordered_set<string> unique_keys;

    for (const vector<string>& row : overall_relation) {

        // 행마다 초기화
        string key = "";

        for (int index : index_list) {
            key += row[index];
            key += "_";
        }

        if (unique_keys.find(key) != unique_keys.end()) {
            return false;
        }

        unique_keys.insert(key);
    }

    // 유일성과 최소성을 모두 만족한 조합 저장
    candidate_keys.push_back(index_list);

    return true;
}

void dfs(int start, int relation_size, int target_size, vector<int>& index_list) {

    // 목표한 크기의 조합이 완성된 경우
    if (index_list.size() == target_size) {

        if (!is_minimal(index_list)) {
            return;
        }

        update(index_list);
        return;
    }

    for (int i = start + 1; i < relation_size; i++) {
        index_list.push_back(i);

        dfs(i, relation_size, target_size, index_list);

        index_list.pop_back();
    }
}

int solution(vector<vector<string>> relation) {

    overall_relation = relation;
    candidate_keys.clear();

    int column_size = overall_relation[0].size();

    vector<int> index_list;

    // 각 조합 크기별 dfs 사용 (키가 적게 사용되는 1개부터 차례로 dfs 적용)
    for (int target_size = 1; target_size <= column_size; target_size++) {

        dfs(-1, column_size, target_size, index_list);
    }

    return candidate_keys.size();
}