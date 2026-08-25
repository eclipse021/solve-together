//
// Created by 임준현 on 26. 8. 25.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

struct human {

    int number;

    int r;
    int c;
    int d;

    int weapon;
    int ability;

    human(int number, int r, int c, int d, int weapon, int ability) {
        this->number = number;
        this->r = r;
        this->c = c;
        this->d = d;
        this->weapon = weapon;
        this->ability = ability;
    }

};

vector<human> humans;

int check_human(int r, int c) {

    for (human h : humans) {

        if (h.r == r && h.c == c) {
            return h.number;
        }

    }

    return -1;
}

struct cmp {
    bool operator()(int a, int b) {
        return a < b;
    }
};

priority_queue<int, vector<int>, cmp> pq[21][21];

void get_weapon(int r, int c, int human_number) {

    pq[r][c].push(humans[human_number].weapon);
    humans[human_number].weapon = pq[r][c].top();

    //cout << "변경된 " << humans[human_number].number << " 의 무기는 " << pq[r][c].top() << "\n";

    pq[r][c].pop();

}


int answer[31];

int main() {

    int n, m, T;
    cin >> n >> m >> T;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n ; j++) {

            int x;
            cin >> x;

            pq[i][j].push(x);
        }
    }

    for (int i = 0; i < m; i++) {

        int in_r, in_c, in_d, in_s;
        cin >> in_r >> in_c >> in_d >> in_s;

        human h = human(i, in_r, in_c, in_d, 0, in_s);
        humans.push_back(h);

        answer[i] = 0;

    }

    for (int test_case = 0; test_case < T; test_case++) {

        for (int now_human = 0; now_human < m ; now_human++) {

            // 1단계
            int nxt_d = humans[now_human].d;

            //cout << humans[now_human].r << " " << humans[now_human].c << "\n";
            int nxt_r = humans[now_human].r + dr[nxt_d];
            int nxt_c = humans[now_human].c + dc[nxt_d];

            // 만약 다음 이동 장소가 격자 밖이면 nxt_r, nxt_c, nxt_d 바꾸기
            if (nxt_r < 1 || nxt_r > n || nxt_c < 1 || nxt_c > n) {

                nxt_d = (nxt_d + 2) % 4;

                nxt_r = humans[now_human].r + dr[nxt_d];
                nxt_c = humans[now_human].c + dc[nxt_d];

            }

            // human 업데이트 전 기존 좌표에 겹치는 사람 있는지 미리 체크
            int another = check_human(nxt_r, nxt_c);

            humans[now_human].r = nxt_r;
            humans[now_human].c = nxt_c;
            humans[now_human].d = nxt_d;


            // 2-1 이동 위치에 다른 사람이 없다면

            if (another == -1) {
                get_weapon(humans[now_human].r, humans[now_human].c, now_human);
                continue;
            }

            // 2-2 이동 위치에 다른 사람이 있다면
            int winner_index;
            int loser_index;

            //cout << now_human << " " << another << "\n";

            // winner, loser 세팅
            if (humans[now_human].weapon + humans[now_human].ability < humans[another].weapon + humans[another].ability) {

                winner_index = another;
                loser_index = now_human;
            }else if (humans[now_human].weapon + humans[now_human].ability > humans[another].weapon + humans[another].ability) {

                winner_index = now_human;
                loser_index = another;
            }else {

                if (humans[now_human].ability < humans[another].ability) {
                    winner_index = another;
                    loser_index = now_human;
                }else {
                    winner_index = now_human;
                    loser_index = another;
                }
            }

            human& winner = humans[winner_index];
            human& loser = humans[loser_index];

            //int point = abs((humans[now_human].weapon + humans[now_human].ability) - (humans[another].weapon + humans[another].ability));
            int point = winner.weapon + winner.ability - (loser.weapon + loser.ability);

            //cout << "winner : " << winner.number << endl;
            //cout << "loser : " << loser.number << "\n";

            answer[winner.number] += point;

            // 2-2-1. 패배한 사람은 무기 내려놓기
            pq[loser.r][loser.c].push(loser.weapon);
            loser.weapon = 0;

            // 2-2-2. 패배한 사람은 다음 위치로 이동 및 총 줍기
            for (int k = 0; k < 4; k++) {

                int loser_nxt_d = (loser.d + k) % 4;
                int loser_nxt_r = loser.r + dr[loser_nxt_d];
                int loser_nxt_c = loser.c + dc[loser_nxt_d];

                // 격자밖으로 이동한다면 이동하지 않기
                if (loser_nxt_r < 1 || loser_nxt_r > n || loser_nxt_c < 1 || loser_nxt_c > n) {
                    continue;
                }

                // 해당 위치에 사람이 있다면 이동하지 않기
                int check = check_human(loser_nxt_r, loser_nxt_c);
                if (check != -1) {
                    continue;
                }

                loser.d = loser_nxt_d;
                loser.r = loser_nxt_r;
                loser.c = loser_nxt_c;

                get_weapon(loser.r, loser.c, loser.number);

                break;
            }

            // 2-2-3. 이긴 사람은 그 자리에서 가장 좋은 총으로 바꾸기
            get_weapon(winner.r, winner.c, winner.number);

        }

    }

    for (int i = 0; i < m; i++) {
        cout << answer[i] << " ";
    }

}
