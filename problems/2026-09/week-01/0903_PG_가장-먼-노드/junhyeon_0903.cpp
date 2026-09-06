#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dist[20001];
vector<int> adj[20001];

int solution(int n, vector<vector<int>> edge) {

    for (int i = 0; i < 20001; i++) {
        dist[i] = -1;
    }

    for (auto e : edge) {

        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);

    }

    queue<int> q;
    q.push(1);
    dist[1] = 0;

    while (!q.empty()) {

        int cur = q.front();
        q.pop();

        for (int nxt : adj[cur]) {

            if (dist[nxt] != -1) {
                continue;
            }

            dist[nxt] = dist[cur] + 1;
            q.push(nxt);

        }

    }

    int max_dist = -1;
    int answer = 0;

    for (int i = 1; i < 20001; i++) {

        if (dist[i] > max_dist) {
            max_dist = dist[i];
            answer = 1;
            continue;
        }

        if (dist[i] == max_dist) {
            answer++;
        }
    }

    return answer;
}