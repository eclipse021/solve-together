//
// Created by 임준현 on 26. 8. 10.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node {

    int time;
    int r;
    int c;
    int jump;

    node(int time, int r, int c, int jump) {
        this->time = time;
        this->r = r;
        this->c = c;
        this->jump = jump;
    }

};

struct cmp {
    bool operator()(const node& x, const node& y) {
        return x.time > y.time;
    }
};

priority_queue<node, vector<node>, cmp> pq;
int times[51][51][6];
const int INF = 2100000000;
char arr[51][51];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void func_jump(int N, node cur) {

    int jump = cur.jump;

    for (int k = 0; k < 4; k++) {

        int next_r = cur.r + dr[k] * jump;
        int next_c = cur.c + dc[k] * jump;

        // 돌이 아닌 지역이면 이동 x
        if (next_r < 1 || next_r > N || next_c < 1 || next_c > N) {
            continue;
        }
        // 도착 지점이 미끄러운 돌이면 이동 x
        if (arr[next_r][next_c] == 'S') {
            continue;
        }

        // 가는 길목 + 도착 지점에 천적이 있으면 이동 x
        bool is_success = true;
        for (int i = 1; i <= jump; i++) {

            int load_r = cur.r + dr[k] * i;
            int load_c = cur.c + dc[k] * i;

            if (arr[load_r][load_c] == '#') {
                is_success = false;
                break;
            }
        }

        if (!is_success) {
            continue;
        }

        pq.push(node(cur.time + 1, next_r, next_c, cur.jump));
    }
}

void func_increase_jump(node cur) {

    if (cur.jump == 5) {
        return;
    }

    int new_jump = cur.jump + 1;

    node new_node = node(cur.time + new_jump*new_jump, cur.r, cur.c, new_jump);
    pq.push(new_node);

}

void func_decrease_jump(node cur) {

    if (cur.jump == 1) {
        return;
    }

    for (int i = 1; i <= cur.jump-1; i++) {
        node new_node = node(cur.time + 1, cur.r, cur.c, i);
        pq.push(new_node);
    }

}


int main() {

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <=N; j++) {

            char x;
            cin >> x;

            arr[i][j] = x;

        }
    }

    int Q;
    cin >> Q;

    for (int test_case = 0; test_case < Q; test_case++) {

        // pq 초기화
        while (!pq.empty()) {
            pq.pop();
        }

        // times 초기화
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                for (int k = 1; k <= 5; k++) {
                    times[i][j][k] = INF;
                }
            }
        }

        int r,c;
        cin >> r >> c;
        pair<int, int> start = {r,c};
        cin >> r >> c;
        pair<int, int> end = {r,c};

        pq.push(node(0, start.first, start.second, 1));

        while (!pq.empty()) {

            auto cur = pq.top();
            pq.pop();

            if (times[cur.r][cur.c][cur.jump] > cur.time) {
                times[cur.r][cur.c][cur.jump] = cur.time;
                func_jump(N, cur);
                func_increase_jump(cur);
                func_decrease_jump(cur);
            }
        }

        int min_value = INF;
        for (int i = 1; i <= 5; i++) {
            min_value = min(min_value, times[end.first][end.second][i]);
        }

        if (min_value == INF) {
            cout << -1 << "\n";
        }else {
            cout << min_value << "\n";
        }

    }

}