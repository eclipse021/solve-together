//
// Created by 임준현 on 26. 8. 21.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int board[11][11] = {0};
int humans[11][11] = {0};
pair<int, int> door;

struct square {

    int r;
    int c;
    int line;

    square(int r, int c, int line) {
        this->r = r;
        this->c = c;
        this->line = line;
    }
};

int main() {

    int N, M, T;
    cin >> N >> M >> T;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x;
            cin >> x;

            board[i][j] = x;
        }
    }

    for (int i = 0; i < M; i++) {
        int human_r, human_c;
        cin >> human_r >> human_c;

        humans[human_r][human_c]++;
    }

    int door_r, door_c;
    cin >> door_r >> door_c;

    door = make_pair(door_r, door_c);

    // 출구 표시
    board[door.first][door.second] = 10;


    int total_distance = 0;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int test_case = 0; test_case < T; test_case++) {

        /*cout << "test_case : " << test_case << "\n";
        cout << "===벽 위치 ====\n";
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }*/


        // 상하좌우 중 출구와 가까워지는 방향으로 이동 1) 상하 2) 좌우
        int temp[11][11] = {0};

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {

                if (humans[i][j] == 0) {
                    continue;
                }

                bool is_move = false;
                for (int k = 0; k < 4; k++) {

                    int nxt_r = i + dr[k];
                    int nxt_c = j + dc[k];

                    // 격자 밖일 경우
                    if (nxt_r < 1 || nxt_r > N || nxt_c < 1 || nxt_c > N) {
                        continue;
                    }

                    // 벽일 경우
                    if (board[nxt_r][nxt_c] >= 1 && board[nxt_r][nxt_c] <= 9) {
                        continue;
                    }

                    int origin_distance = abs(door.first - i) + abs(door.second - j);
                    int new_distance = abs(door.first - nxt_r) + abs(door.second - nxt_c);

                    if (origin_distance <= new_distance) {
                        continue;
                    }

                    temp[nxt_r][nxt_c] += humans[i][j];
                    total_distance += humans[i][j];
                    is_move = true;
                    break;

                }

                // 만약 이동하지 않았더라도 temp에 값 저장
                if(!is_move) {
                    temp[i][j] += humans[i][j];
                }
            }
        }

        // humans 동시 업데이트
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j<=N; j++) {
                humans[i][j] = temp[i][j];
            }
        }

        // 탈출구로 통과했으면 그 좌표의 사람 0으로 만들기
        humans[door.first][door.second] = 0;

        // 점검 -> 만약 모든 사람이 탈출했다면 거기서 종료
        bool is_finish = true;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (humans[i][j] != 0) {
                    is_finish = false;
                }
            }
        }

        // 만약 전부 탈출했다면 종료
        if (is_finish) {
            cout << total_distance << "\n";
            cout << door.first << " " << door.second << "\n";

            return 0;
        }


        // 미로 회전
        // 우선 참가자 리스트 모으기

        vector<pair<int, int>> candidates;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (humans[i][j] == 0) {
                    continue;
                }

                candidates.push_back(make_pair(i,j));
            }
        }

        // 각 참가자 마다 square 리스트 만들기
        vector<square> squares;

        for (auto now : candidates) {

            // 한 변 길이 정하기
            int line = max(abs(door.first - now.first), abs(door.second - now.second));

            // 좌상단 r,c 정하기
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    int start_r = i;
                    int end_r = i + line;
                    int start_c = j;
                    int end_c = j + line;

                    if (end_r < 1 || end_r > N || end_c < 1 || end_c > N) {
                        continue;
                    }

                    if (!(now.first >= start_r && now.first <= end_r && now.second >= start_c && now.second <= end_c)) {
                        continue;
                    }

                    if (!(door.first >= start_r && door.first <= end_r && door.second >= start_c && door.second <= end_c)) {
                        continue;
                    }

                    square s = square(start_r, start_c, line);
                    squares.push_back(s);
                }
            }
        }

        // 모든 square list 중 가장 작은 정사각형 찾기
        square now_square = squares[0];

        for (auto s : squares) {

            if (s.line < now_square.line) {
                now_square = s;
                continue;
            }

            if (s.line == now_square.line) {
                if (s.r < now_square.r) {
                    now_square = s;
                    continue;
                }

                if (s.r == now_square.r) {
                    if (s.c < now_square.c) {
                        now_square = s;
                        continue;
                    }
                }
            }

        }

        //cout << "test_case : " << test_case <<"\n";
        //cout << "찾은 정사각형 정보 : r -> " << now_square.r << " " << " c ->  " << now_square.c << " line -> " << now_square.line << "\n";


        // 찾은 정사각형에 대해 회전하기
        int rotate_board[11][11] = {0};
        int rotate_humans[11][11] = {0};

        int start_r = now_square.r;
        int start_c = now_square.c;
        int end_r = now_square.r + now_square.line;
        int end_c = now_square.c + now_square.line;

        for (int i = 0; i <= now_square.line; i++) {
            for (int j = 0; j <= now_square.line; j++) {

                int origin_r = start_r + i;
                int origin_c = start_c + j;

                //cout << "원래 좌표 : origin_r : " << origin_r << " origin_c : " << origin_c << "\n";
                //cout << "변환 좌표 : rotate_r : " << start_r + j << " rotate_c : " << end_c - i << "\n";
                rotate_board[start_r + j][end_c - i] = board[origin_r][origin_c];
                rotate_humans[start_r + j][end_c - i] = humans[origin_r][origin_c];
                //cout << "그 때 원래 좌표의 사람 숫자 : " << humans[origin_r][origin_c] << "\n";

            }
        }

        // 1~9인 벽에 대해 내구도 감소 및 board/humans 복제
        for (int i = 0; i <= now_square.line; i++) {
            for (int j = 0; j <= now_square.line; j++) {

                int origin_r = start_r + i;
                int origin_c = start_c + j;

                if (rotate_board[origin_r][origin_c] >= 1 && rotate_board[origin_r][origin_c] <= 9) {
                    rotate_board[origin_r][origin_c]--;
                }

                board[origin_r][origin_c] = rotate_board[origin_r][origin_c];
                humans[origin_r][origin_c] = rotate_humans[origin_r][origin_c];

            }
        }

        // 출구 업데이트
        for (int i = 1; i<= N; i++) {
            for (int j = 1; j<=N; j++) {
                if (board[i][j] == 10) {
                    door = make_pair(i,j);
                }
            }
        }

        /*cout << "===사람 위치 - 회전 이후  ===\n";
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cout << humans[i][j] << " ";
            }
            cout << "\n";
        }*/
        //cout <<"새롭게 업데이트 된 출구 위치 " << door.first << " " << door.second << "\n";
    }

    /*cout << "test_case : " << "final" << "\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }*/

    cout << total_distance << "\n";
    cout << door.first << " " << door.second << "\n";

    return 0;
}