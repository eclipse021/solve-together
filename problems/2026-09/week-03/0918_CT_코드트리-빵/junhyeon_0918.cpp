#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

bool basecamp[15][15] = {false};
bool load[15][15];

struct human {

    int r;
    int c;

    pair<int, int> target;
    bool finish;

    human() {
        this->r = -1;
        this->c = -1;

        finish = true;
    }

    human(int r, int c, pair<int, int> target) {
        this->r = r;
        this->c = c;

        this->target = target;
        finish = false;
    }

};

human humans[31];
const int INF = 210000000;

int main() {

    int n,m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            int x;
            cin >> x;

            if (x == 0) {
                basecamp[i][j] = false;
            }else {
                basecamp[i][j] = true;
            }

            load[i][j] = true;

        }
    }

    int t = 1;

    int dr[4] = {-1, 0, 0, 1};
    int dc[4] = {0, -1, 1, 0};

    while (true) {

        /*cout << "현재 t분 : " << t << "\n";
        cout << "===사람 위치===\n";*/

        // 1. 현재 도착하지 않은 사람들 전부 이동
        int test_case = min(t, m+1);

        for (int i = 1; i < test_case; i++) {

            //cout << i << "번째 : " << humans[i].r << " " << humans[i].c << "\n";

        }

        /*cout << "=== load 위치 ===\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << load[i][j] << " ";
            }
            cout << "\n";
        }*/


        for (int i = 1; i < test_case; i++) {
            // 도착한 사람이면 이동 x
            if (humans[i].finish) {
                continue;
            }

            bool visited[15][15] = {false};
            pair<int, int> move[15][15];
            queue<pair<int, int>> q;

            visited[humans[i].r][humans[i].c] = true;
            move[humans[i].r][humans[i].c] = {-1, -1};
            q.push({humans[i].r, humans[i].c});

            while (!q.empty()) {

                auto cur = q.front();
                q.pop();

                if (cur == humans[i].target) {
                    break;
                }

                for (int k = 0; k < 4; k++) {

                    int nxt_r = cur.first + dr[k];
                    int nxt_c = cur.second + dc[k];

                    if (nxt_r < 0 || nxt_r >= n || nxt_c < 0 || nxt_c >= n) {
                        continue;
                    }

                    if (!load[nxt_r][nxt_c]) {
                        continue;
                    }

                    if (visited[nxt_r][nxt_c]) {
                        continue;
                    }

                    visited[nxt_r][nxt_c] = true;
                    move[nxt_r][nxt_c] = make_pair(cur.first, cur.second);
                    q.push(make_pair(nxt_r, nxt_c));

                }
            }

            int now_r = humans[i].target.first;
            int now_c = humans[i].target.second;

            while (true) {

                int nxt_r = move[now_r][now_c].first;
                int nxt_c = move[now_r][now_c].second;

                if (nxt_r == humans[i].r && nxt_c == humans[i].c) {
                    break;
                }

                now_r = nxt_r;
                now_c = nxt_c;
            }

            humans[i].r = now_r;
            humans[i].c = now_c;
        }

        // 2. 편의점 위치에 있으면 도착 표시하고 load 업데이트
        for (int i = 1; i < test_case; i++) {

            // 이미 도착한 사람이면 건너뛰기
            if (humans[i].finish) {
                continue;
            }

            if (humans[i].r == humans[i].target.first && humans[i].c == humans[i].target.second) {
                humans[i].finish = true;
                load[humans[i].r][humans[i].c] = false;
            }

        }

        // 종료됐는지 검사 1. t가 m보다 큰지(모든 사용자) 2. 전부 다 도착했는지
        if (t > m) {

            bool is_success = true;
            for (int i = 1; i <=m ; i++) {
                if (!humans[i].finish) {
                    is_success = false;
                }
            }

            if (is_success) {
                cout << t << "\n";
                return 0;
            }
        }


        // 3. t<=m 이면 주변에 가장 가까운 베이스 캠프로 들어감 + load 업데이트
        if (t <= m) {

            int t_r, t_c;
            cin >> t_r >> t_c;

            //cout << "입력된 t_r : " << t_r << "  입력된 t_c : " << t_c << "\n";

            t_r -=1;
            t_c -=1;

            bool visited[15][15] = {false};
            int dist[15][15];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = INF;
                }
            }

            queue<pair<int, int>> q;

            visited[t_r][t_c] = true;
            q.push({t_r, t_c});
            dist[t_r][t_c] = 0;

            while (!q.empty()) {

                auto cur = q.front();
                q.pop();

                for (int k = 0; k < 4; k++) {

                    int nxt_r = cur.first + dr[k];
                    int nxt_c = cur.second + dc[k];

                    if (nxt_r < 0 || nxt_r >= n || nxt_c < 0 || nxt_c >= n) {
                        continue;
                    }

                    if (!load[nxt_r][nxt_c]) {
                        continue;
                    }

                    if (visited[nxt_r][nxt_c]) {
                        continue;
                    }

                    visited[nxt_r][nxt_c] = true;
                    q.push(make_pair(nxt_r, nxt_c));
                    dist[nxt_r][nxt_c] = dist[cur.first][cur.second] + 1;

                }

            }

            int now_dist = INF;
            int b_r, b_c;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    //cout << basecamp[i][j] << " " << dist[i][j] << "\n";
                    if (basecamp[i][j] && dist[i][j] < now_dist) {
                        b_r = i;
                        b_c = j;
                        now_dist = dist[i][j];
                    }

                }
            }

            load[b_r][b_c] = false;
            humans[t] = human(b_r, b_c, make_pair(t_r, t_c));

            //cout << "b_r : " << b_r << "  b_c : " << b_c << "\n";


        }

        t++;
    }

}