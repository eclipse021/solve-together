//
// Created by 임준현 on 26. 7. 18.
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct node {

    int dist;
    int number;
    int prev_dist;

    node(int dist, int number, int prev_dist) {
        this->dist = dist;
        this->number = number;
        this->prev_dist = prev_dist;
    }
};

struct cmp {
    bool operator()(node n1, node n2) {
        return n1.dist > n2.dist;
    }
};

// (거리, 번호) 쌍으로 인접 연결 리스트 저장
vector<pair<int, int>> adj[50001];
// 산 정상인지 판별 목적
bool is_summit[50001];

// arr 초기화 변수(무한대)
const int INF = 2100000000;
int arr[50001];

// [0]: 거리, [1]: 번호
vector<int> answer;

void update(vector<int> candidate) {
    // 거리가 더 짧은게 오면 교체
    if (candidate[0] < answer[0]) {
        answer = candidate;
        return;
    }

    // 거리가 같을 경우 번호가 더 짧은게 오면 교체
    if (candidate[0] == answer[0]) {
        if (candidate[1] < answer[1]) {
            answer = candidate;
            return;
        }
    }
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {

    // paths 를 adj로 초기화
    for (vector<int> path : paths) {

        adj[path[0]].push_back(make_pair(path[2], path[1]));
        adj[path[1]].push_back(make_pair(path[2], path[0]));

    }


    for (int i = 0; i < 50001; i++) {
        is_summit[i] = false;
    }
    // 산 정상인 부분 저장
    for (int summit : summits) {
        is_summit[summit] = true;
    }


    // 모든 arr 무한대로 초기화
    for (int i = 0; i < 50001; i++) {
        arr[i] = INF;
    }

    // 시작 부분은 0으로 초기화
    for (int gate : gates) {
        arr[gate] = 0;
    }

    // answer 초기화
    answer.push_back(INF);
    answer.push_back(INF);

    priority_queue<node, vector<node>, cmp> pq;
    for (int gate : gates) {

        // 모든 출발점의 연결된 원소를 pq에 저장
        for (pair<int, int> cur : adj[gate]) {
            pq.push(node(cur.first, cur.second, 0));
        }
    }

    while (!pq.empty()) {

        auto cur = pq.top();
        pq.pop();

        int now_dist = max(cur.dist, cur.prev_dist);

        if (now_dist < arr[cur.number]) {
            arr[cur.number] = now_dist;

            // 산 정상일 경우 더 진행하지 않고 answer 업데이트
            if (is_summit[cur.number]) {
                vector<int> candidate;
                candidate.push_back(now_dist);
                candidate.push_back(cur.number);

                update(candidate);
                continue;
            }

            // 봉우리가 아닐 경우 인접한 후보군 pq에 추가
            for (pair<int, int> nxt : adj[cur.number]) {
                pq.push(node(nxt.first, nxt.second, now_dist));
            }
        }

    }

    vector<int> result;
    result.push_back(answer[1]);
    result.push_back(answer[0]);

    return result;
}