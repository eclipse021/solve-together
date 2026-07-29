//
// Created by 임준현 on 26. 7. 29.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<int> numbers;
int min_value;
int max_value;

void update(vector<int> index_list) {

    int result = numbers[0];

    for (int i = 0; i < index_list.size(); i++) {
        int symbol_int = index_list[i];
        int num = numbers[i+1];

        if (symbol_int == 0) {
            result += num;

        }else if (symbol_int == 1) {
            result -= num;

        }else if (symbol_int == 2) {
            result *= num;

        }else if (symbol_int == 3) {
            result /= num;

        }
    }

    min_value = min(min_value, result);
    max_value = max(max_value, result);

}

void dfs(vector<int> index_list, vector<int> remain, int target) {

    if (index_list.size() == target) {
        update(index_list);
        return;
    }

    for (int i = 0; i < remain.size(); i++) {

        if (remain[i] == 0) {
            continue;
        }

        index_list.push_back(i);
        remain[i]--;
        dfs(index_list, remain, target);
        remain[i]++;
        index_list.pop_back();

    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int test = 1; test<= T; test++) {

        // 전역변수 초기화
        numbers.clear();
        min_value = 2100000000;
        max_value = -2100000000;
        vector<int> remain;

        // 사용될 숫자 갯수
        int N;
        cin >> N;

        // 사용할 문자열를 symbols에 저장
        // [0]: + 개수, [1]: - 개수, [2]: * 개수, [3]: / 개수
        for (int i = 0; i < 4; i++) {
            int x;
            cin >> x;

            remain.push_back(x);
        }

        // 사용할 숫자를 numbers에 저장
        for (int i = 0; i <N; i++) {
            int x;
            cin >> x;

            numbers.push_back(x);
        }

        // ---------- 여기까지 변수 세팅 ---------- //

        // dfs 시작
        vector<int> index_list;
        dfs(index_list, remain, N-1);


        int answer = abs(max_value - min_value);
        cout << "#" << test << " " << answer << endl;

    }


}