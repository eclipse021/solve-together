//
// Created by 임준현 on 26. 7. 27.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

struct node {
    int r;
    int c;
    int dist;

    node(int dist, int r, int c) {
        this->dist = dist;
        this->r = r;
        this->c = c;
    }
};

struct cmp {

    bool operator()(node& a, node& b) {
        return a.dist > b.dist;
    }

};

const int INF = 2100000000;
vector<node> adj[100][100];
int arr[100][100];
int dist[100][100];


int main() {

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                adj[i][j].clear();
                dist[i][j] = INF;
                arr[i][j] = 0;
            }
        }

        int N;
        cin >> N;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char c;
                cin >> c;

                arr[i][j] = c-'0';
            }
        }

        int dc[4] = {-1, 0, 1, 0};
        int dr[4] = {0, 1, 0, -1};

        for (int i = 0; i < N; i++) {
            for (int j = 0; j <N; j++) {
                for (int k = 0; k <4; k++) {
                    int r = i + dr[k];
                    int c = j + dc[k];

                    if (r < 0 || r >= N || c < 0 || c >= N) {

                        continue;
                    }

                    adj[i][j].push_back(node(arr[r][c], r, c));
                }

            }
        }

        priority_queue<node, vector<node>, cmp> pq;
        pq.push(node(0, 0, 0));

        while (!pq.empty()) {

            auto cur = pq.top();
            pq.pop();

            if (cur.dist >= dist[cur.r][cur.c]) {
                continue;
            }

            dist[cur.r][cur.c] = cur.dist;
            for (auto nxt : adj[cur.r][cur.c]) {

                pq.push(node(dist[cur.r][cur.c] + nxt.dist, nxt.r, nxt.c));
            }

        }


        cout << "#" << test_case << " " << dist[N-1][N-1] << "\n";
    }

}