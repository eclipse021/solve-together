#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int INF = 210000000;

vector<int> solution(vector<string> gems) {

    unordered_set<string> us;
    for (string gem : gems) {
        us.insert(gem);
    }


    unordered_map<string, int> um;
    for (string s : us) {
        um[s] = 0;
    }
    int diff_count = um.size();

    // dp INF로 초기화
    int dp[100001];
    for (int i = 0; i < 100001; i++) {
        dp[i] = INF;
    }
    // 현재 diff_count
    int now_diff_count = 0;

    // 각 인덱스 시작 지점 설정
    int diff_index = -1;
    int dp_index = -1;


    // 슬라이딩 시작
    while (true) {

        if (now_diff_count < diff_count) {
            diff_index++;

            if (diff_index >= gems.size()) {
                break;
            }

            string  s = gems[diff_index];

            if (um[s] == 0) {
                now_diff_count++;
            }
            um[s]++;

            //cout << "now_diff_cout < diff_count : " << s << "\n";

        }else {

            dp_index++;
            if (dp_index >= gems.size()) {
                break;
            }

            dp[dp_index] = diff_index;
            string s = gems[dp_index];
            if (um[s] == 1) {
                now_diff_count--;
            }
            um[s]--;


        }

    }

    int min_value = INF;
    int min_index = INF;

    // 전체 dp 중 dp 최소값 찾기
    for (int i = 0; i < gems.size(); i++) {

        if (min_value > dp[i] - i) {
            min_value = dp[i] - i;
            min_index = i;
        }
    }

    // 찾은 최소값, 인덱스 반환
    vector<int> answer;
    answer.push_back(min_index + 1);
    answer.push_back(dp[min_index] + 1);


    return answer;
}