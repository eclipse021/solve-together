#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool visited[51][51];
int board[51][51];

int dr[4] = {0, 1, 0, -1};
int dc[4] = {-1, 0, 1, 0};

struct Whale {
    int r;
    int c;
    int d;

    Whale(int r, int c, int d) {
        this->r = r;
        this->c = c;
        this->d = d;
    }
};

bool check(int r, int c, int N) {

    if (r < 1 || r > N || c < 1 || c > N ) {
        return false;
    }

    if (board[r][c] == 1) {
        return false;
    }

    if (visited[r][c]) {
        return false;
    }

    return true;
}

int main() {

    // 값 초기화
    for (int i = 1; i < 51; i++) {
        for (int j = 1; j < 51; j++) {
            visited[i][j] = false;
            board[i][j] = 0;
        }
    }

    int N, w_r, w_c, w_d;
    cin >> N >> w_r >> w_c >> w_d;

    // 방향 세팅
    if (w_d == 1) {
        w_d = 3;
    }else if (w_d == 2) {
        w_d = 1;
    }else if (w_d == 3) {
        w_d = 0;
    }else if (w_d == 4) {
        w_d = 2;
    }

    Whale whale = Whale(w_r, w_c, w_d);

    // 처음 위치는 방문 표시 + 출력
    visited[w_r][w_c] = true;
    cout << whale.r << " " << whale.c << "\n";

    // board 세팅
    for (int i = 1; i <=N; i++) {
        for (int j = 1; j <=N ; j++) {
            int x;
            cin >> x;

            board[i][j] = x;
        }
    }

    while (true) {

        // 1단계 확인

        // 1) 직진 가능한지
        int nxt_d = whale.d;

        int nxt_r = whale.r + dr[nxt_d];
        int nxt_c = whale.c + dc[nxt_d];

        if (check(nxt_r, nxt_c, N)) {

            //cout << "1단계 중 정면 직진 \n";

            whale.r = nxt_r;
            whale.c = nxt_c;
            whale.d = nxt_d;

            visited[whale.r][whale.c] = true;
            cout << whale.r << " " << whale.c << "\n";

            continue;
        }

        // 2) 좌회전 후 직진
        nxt_d = (whale.d + 1) % 4;
        nxt_r = whale.r + dr[nxt_d];
        nxt_c = whale.c + dc[nxt_d];

        if (check(nxt_r, nxt_c, N)) {

            //cout << "1단계 중 좌회전 후 직진 \n";


            whale.r = nxt_r;
            whale.c = nxt_c;
            whale.d = nxt_d;

            visited[whale.r][whale.c] = true;
            cout << whale.r << " " << whale.c << "\n";

            continue;
        }

        // 3) 우회전 후 직진
        nxt_d = (whale.d + 4 - 1) % 4;
        nxt_r = whale.r + dr[nxt_d];
        nxt_c = whale.c + dc[nxt_d];

        if (check(nxt_r, nxt_c, N)) {

            //cout << "1단계 중 우회전 후 직진 \n";


            whale.r = nxt_r;
            whale.c = nxt_c;
            whale.d = nxt_d;

            visited[whale.r][whale.c] = true;
            cout << whale.r << " " << whale.c << "\n";

            continue;
        }

        // 4) 반대 방향으로 돈 후 직진
        nxt_d = (whale.d + 2) % 4;
        nxt_r = whale.r + dr[nxt_d];
        nxt_c = whale.c + dc[nxt_d];

        if (check(nxt_r, nxt_c, N)) {

            //cout << "1단계 중 반대 전환 후 직진 \n";


            whale.r = nxt_r;
            whale.c = nxt_c;
            whale.d = nxt_d;

            visited[whale.r][whale.c] = true;
            cout << whale.r << " " << whale.c << "\n";

            continue;
        }

        // 2단계 확인

        //cout << "2단계 돌입\n";
        const int INF = 99999;

        int dist[51][51];
        pair<int, int> prev_pos[51][51];

        // 초기화
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dist[i][j] = INF;
                prev_pos[i][j] = make_pair(0,0);
            }
        }

        queue<pair<int, int>> q;
        q.push(make_pair(whale.r, whale.c));
        dist[whale.r][whale.c] = 0;

        while (!q.empty()) {

            auto cur = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {

                int new_r = cur.first + dr[k];
                int new_c = cur.second + dc[k];

                // 격자 밖으로 넘어갈 때
                if (new_r < 1 || new_r > N || new_c < 1 || new_c > N) {
                    continue;
                }

                // 벽일 때
                if (board[new_r][new_c] == 1) {
                    continue;
                }

                /*// 이미 방문한 공간
                if (visited[new_r][new_c]) {
                    continue;
                }*/

                // 이미 표시한 공간
                if (dist[new_r][new_c] != INF) {
                    continue;
                }

                dist[new_r][new_c] = dist[cur.first][cur.second] + 1;
                prev_pos[new_r][new_c] = make_pair(cur.first, cur.second);
                q.push(make_pair(new_r, new_c));

            }
        }

        /*cout << "dist 관찰\n";
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cout << dist[i][j] << " ";
            }
            cout << "\n";
        }*/

        // 가장 가까운 바다 찾기
        bool is_find = false;
        int now_dist = INF;
        pair<int, int> next_pos;

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {

                if (dist[i][j] < now_dist && !visited[i][j] && board[i][j] == 0) {
                    now_dist = dist[i][j];
                    next_pos = make_pair(i, j);
                    is_find = true;
                }

            }
        }

        // 만약 이동할 바다가 없다면 -> 종료
        if (!is_find) {
            return 0;
        }

        // 이동할 바다가 있다면 -> 위치/방향 이동 + visited 변경 및 출력
        whale.r = next_pos.first;
        whale.c = next_pos.second;

        if (whale.r - 1 == prev_pos[whale.r][whale.c].first && whale.c == prev_pos[whale.r][whale.c].second) {
            // 아래로 이동
            whale.d = 1;

        }else if(whale.r + 1 == prev_pos[whale.r][whale.c].first && whale.c == prev_pos[whale.r][whale.c].second) {
            // 위로 이동
            whale.d = 3;

        }else if (whale.r == prev_pos[whale.r][whale.c].first && whale.c - 1 == prev_pos[whale.r][whale.c].second) {
            // 우로 이동
            whale.d = 2;

        }else if (whale.r == prev_pos[whale.r][whale.c].first && whale.c + 1== prev_pos[whale.r][whale.c].second){
            // 좌로 이동
            whale.d = 0;

        }

        visited[whale.r][whale.c] = true;
        cout << whale.r << " " << whale.c << "\n";
    }

}