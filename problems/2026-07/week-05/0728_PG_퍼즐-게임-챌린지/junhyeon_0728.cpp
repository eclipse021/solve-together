//
// Created by 임준현 on 26. 7. 28.
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#define ll long long

using namespace std;

vector<int> overall_diffs;
vector<int> overall_times;
ll overall_limit;

bool check(int level) {

    ll now_time = 0;

    for (int i = 0; i < overall_diffs.size(); i++) {

        // 내 레벨이 문제 난이도 보다 높으면 한번에 통과
        if (overall_diffs[i] <= level) {
            now_time += overall_times[i];
        }else { // 내 레벨보다 문제 난이도가 높을 경우

            ll retry_count = overall_diffs[i] - level;
            ll prev_time = (overall_times[i-1] + overall_times[i]) * retry_count;
            now_time += prev_time;

            now_time += overall_times[i];
        }

        if (now_time > overall_limit) {
            return false;
        }

    }

    //cout << "level: " << level << "," <<  " 지금 시간 : "<< now_time << "\n";
    return true;

}

ll answer;

void binary_search(int start, int end) {

    if (start > end) {
        return;
    }

    int mid = (start + end) / 2;

    bool is_check = check(mid);

    if (!is_check) {

        binary_search(mid+1, end);
    }else {

        // 최소가 되는 레벨 (현재 상태는 true, 바로 왼쪽은 false 일 때)
        if (mid == 1 || !check(mid-1)) {
            answer = mid;
            return;
        }

        binary_search(start, mid-1);
    }
}

int solution(vector<int> diffs, vector<int> times, long long limit) {

    overall_diffs = diffs;
    overall_times = times;
    overall_limit = limit;

    binary_search(1, 100000);

    return answer;
}