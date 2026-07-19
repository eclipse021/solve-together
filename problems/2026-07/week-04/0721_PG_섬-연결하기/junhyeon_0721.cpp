//
// Created by 임준현 on 26. 7. 19.
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// 인접 연결 리스트(연결된 노드 정보 저장)
vector<pair<int,int>> adj[102];

// 해당 노드를 반복했는지 파악하기 위한 배열
int arr[102];

// arr에 채워져있는 값 (아직 방문 안 함 표현)
const int INF = 2100000000;
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

int solution(int n, vector<vector<int>> costs) {

    // adj 초기화
    for (vector<int> cost : costs) {
        adj[cost[0]].push_back(make_pair(cost[2], cost[1]));
        adj[cost[1]].push_back(make_pair(cost[2], cost[0]));
    }

    // arr 초기화
    for (int j = 0; j < 101; j++) {
        arr[j] = INF;
    }

    // 0을 프림 알고리즘 시작점으로 세팅 -> 0에 이웃한 노드 pq에 저장
    for (int j = 0; j < adj[0].size(); j++) {
        pq.push(make_pair(adj[0][j].first, adj[0][j].second));
    }
    // 0 방문 표시
    arr[0] = 0;
    int total = 0;

    while (!pq.empty()) {

        auto cur = pq.top();
        pq.pop();

        int dist = cur.first;
        int number = cur.second;

        // 방문 했으면 넘어가기 -> 방문 유무보다 최소값인지 비교한 다익스트라와 차이!
        if (arr[number] != INF) {
            continue;
        }

        arr[number] = 0;
        total += dist;

        for (auto nxt : adj[number]) {
            pq.push(make_pair(nxt.first, nxt.second));
        }
    }

    return total;
}