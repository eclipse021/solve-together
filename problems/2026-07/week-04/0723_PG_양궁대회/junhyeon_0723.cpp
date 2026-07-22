//
// Created by 임준현 on 26. 7. 23.
//
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iostream>

#define ll long long

using namespace std;

// 1, 100, 10,000, 1,000,000 ...
ll mul[11];

// 기존에 존재하는 조합인지 검사하는 set
unordered_set<ll> us;

// points가 기존에 존재하는 조합이 있는지 검사하는 메서드
bool is_find(int points[11]) {

    ll target = 0;
    for (int i = 0; i < 11; i++) {
        target += points[10-i] * mul[i];
    }

    // 기존에 존재하는 조합
    if (us.find(target) != us.end()) {
        return true;
    }

    // 기존에 존재하지 않은 조합
    us.insert(target);
    return false;
}

// 어피치 정보
vector<int> peach_info;
// 현재까지 라이언의 최고 득점
ll now_max_diff = 0;
// 새로운 점수와 동률일 경우 비교할 값 (각 자리 수 마다 100의 자리수를 곱한 수의 총합, 해당 총합이 작은 수를 선택)
ll now_total = 0;
// 현재까지 라이언 최고 득점 조합
vector<int> answer;

// now_total 계산 메서드
// 해당 total 값이 클 수록 가장 작은 값이 더 많이 분포됨
ll calculate_now_total(int points[11]) {

    ll total = 0;
    for (int i = 0; i < 11; i++) {
        total += points[i] * mul[i];
    }

    return total;
}

void update(int points[11]) {

    int rion_point = 0;
    int peach_point = 0;

    for (int i = 0; i < 11; i++) {

        if (points[i] == 0 && peach_info[i] == 0) {
            continue;
        }

        if (points[i] <= peach_info[i]) {
            peach_point += 10-i;
        } else {
            rion_point += 10-i;
        }
    }

    // 문제점: 라이언과 어피치의 점수 차이
    int score_diff = rion_point - peach_point;

    // 어피치가 우승하거나 비기는 경우
    if (score_diff <= 0) {
        return;
    }

    // 1. 기존 answer가 없을 경우 answer 등록
    if (answer.empty()) {
        for (int i = 0; i < 11; i++) {
            answer.push_back(points[i]);
        }

        // 문제점: 라이언 점수가 아니라 점수 차이 저장
        now_max_diff = score_diff;
        now_total = calculate_now_total(points);

        return;
    }

    // 2. 기존 점수 차이가 현재 점수 차이보다 클 경우
    if (now_max_diff > score_diff) {
        return;
    }

    // 3. 기존 점수 차이보다 현재 점수 차이가 더 클 경우
    if (now_max_diff < score_diff) {
        while (!answer.empty()) {
            answer.pop_back();
        }

        for (int i = 0; i < 11; i++) {
            answer.push_back(points[i]);
        }

        now_max_diff = score_diff;
        now_total = calculate_now_total(points);
        return;
    }

    // 4. 기존 점수 차이와 새로운 점수 차이가 같은 경우
    if (now_max_diff == score_diff) {

        ll total = calculate_now_total(points);

        if (total > now_total) {

            while (!answer.empty()) {
                answer.pop_back();
            }

            for (int i = 0; i < 11; i++) {
                answer.push_back(points[i]);
            }

            now_max_diff = score_diff;
            now_total = total;
        }
    }
}


void dfs(int now_n, int target_n, int points[11]) {

    if (now_n == target_n) {
        update(points);
        return;
    }

    for (int i = 0; i < 11; i++) {
        points[i] += 1;

        if (!is_find(points)) {
            dfs(now_n + 1, target_n, points);
        }

        points[i] -= 1;

    }
}

vector<int> solution(int n, vector<int> info) {

    // peach info 초기화 (전역변수)
    peach_info = info;

    //mul 초기화
    for (int i = 0; i < 11; i++) {
        if (i == 0) {
            mul[i] = 1;
            continue;
        }
        mul[i] = mul[i-1] * 20;
    }


    // points 초기화
    int points[11];
    for (int i = 0; i < 11; i++) {
        points[i] = 0;
    }

    dfs(0, n, points);

    if (answer.empty()) {
        answer.push_back(-1);
        return answer;
    }

    return answer;
}