//
// Created by 임준현 on 26. 7. 16.
//
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <unordered_set>

using namespace std;

int compare(vector<int> queue1, vector<int> queue2) {

    // dp: 해당 순서까지의 queue1 누적합 저장 (queue2 원소 들어올 양, +30만)
    long long dp[600000];

    // dp 초기화
    for (int i = 0; i < queue1.size(); i++) {
        if (i == 0) {
            dp[i] = queue1[i];
            continue;
        }

        dp[i] = dp[i-1] + queue1[i];
    }

    // dp 값 존재 유무를 O(1)로 확인할 수 있게 set 생성
    unordered_set<long long> us;
    for (int i = 0; i < queue1.size(); i++) {
        us.insert(dp[i]);
    }

    // sum: queue1, queue2 전체 원소의 합, target: 큐 한 개에 있어야 할 목표합
    long long sum = 0;
    for (int i = 0; i < queue1.size(); i++) {
        sum += queue1[i];
        sum += queue2[i];
    }
    long long target = sum/2;

    long long now = dp[queue1.size()-1];
    // 이미 queue1의 전체합이 target 이면 return 0
    if (now == target) {
        return 0;
    }


    // if) queue2 를 뒤에 안 넣어도 끝나는 경우(queue1에서 원소만 제거) 계산
    if (us.find(now-target) != us.end()) {
        for (int j = 1; j <= queue1.size(); j++) {
            if (dp[j-1] == now -target) {
                return j;
            }
        }
    }

    // else if) queue2를 뒤에 넣어야 하는 경우 계산
    for (int i = 1; i <= queue2.size(); i++) {

        queue1.push_back(queue2[i-1]);
        now += queue2[i-1];

        dp[queue1.size()-1] = dp[queue1.size()-2] + queue2[i-1];
        us.insert(dp[queue1.size()-1]);

        if (now == target) {
            return i;
        }

        if (us.find(now-target) != us.end()) {
            for (int j = 1; j <= queue1.size(); j++) {
                if (dp[j-1] == now -target) {
                    return i+j;
                }
            }
        }

    }

    return -1;

}

int solution(vector<int> queue1, vector<int> queue2) {

    int answer1 = compare(queue1, queue2);
    int answer2 = compare(queue2, queue1);

    if (answer1 == -1 && answer2 == -1) {
        return -1;
    }

    if (answer1 == -1) {
        return answer2;
    }

    if (answer2 == -1) {
        return answer1;
    }

    return min(answer1, answer2);

}