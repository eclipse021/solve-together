#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int arr[74][74];

struct Robot {

    pair<int, int> pos[5]; // top : 0, right : 1, bottom : 2, left : 3, mid : 4
    int d;

    Robot(int c, int d) {

        pos[0] = {1,c};
        pos[1] = {2, c+1};
        pos[2] = {3, c};
        pos[3] = {2, c-1};
        pos[4] = {2, c};

        this->d = d;
    }

    Robot() {
        // 기본 생성자
    }

    void move_bottom() {
        for (int i = 0; i < 5; i++) {
            pos[i].first += 1;
        }
    }

    void move_left() {
        for (int i = 0; i < 5; i++) {
            pos[i].first += 1;
            pos[i].second -= 1;
        }

        this->d = (this->d + 3) % 4;
    }

    void move_right() {
        for (int i = 0; i <5 ; i++) {
            pos[i].first += 1;
            pos[i].second += 1;
        }

        this->d = (this->d + 1) % 4;
    }
};

Robot robots[1001];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int R, C, T;

int down_dr[3] = {0, 1, 0};
int down_dc[3] = {-1, 0, 1};

bool check_down(pair<int, int> standard) {

    for (int k = 0; k < 3; k++) {
        int nxt_r = standard.first + down_dr[k];
        int nxt_c = standard.second + down_dc[k];

        if (nxt_r > R + 3 || nxt_c < 1 || nxt_c > C ) {
            return false;
        }

        if (arr[nxt_r][nxt_c] != 0) {
            return false;
        }
    }

    return true;
}

int left_dr[5] = {-1, 0, 1, 1, 2};
int left_dc[5] = {0, -1, 0, -1, 0};
bool check_left(pair<int, int> standard) {

    for (int k = 0; k < 5; k++) {
        int nxt_r = standard.first + left_dr[k];
        int nxt_c = standard.second + left_dc[k];

        if (nxt_r > R + 3 || nxt_c < 1 || nxt_c > C ) {
            return false;
        }

        if (arr[nxt_r][nxt_c] != 0) {
            return false;
        }
    }

    return true;

}

int right_dr[5] = {-1, 0, 1, 1, 2};
int right_dc[5] = {0, 1, 0, 1, 0};

bool check_right(pair<int, int> standard) {

    for (int k = 0; k < 5; k++) {
        int nxt_r = standard.first + right_dr[k];
        int nxt_c = standard.second + right_dc[k];

        if (nxt_r > R + 3 || nxt_c < 1 || nxt_c > C ) {
            return false;
        }

        if (arr[nxt_r][nxt_c] != 0) {
            return false;
        }
    }

    return true;
}


int out_dr[5] = {-1, 0, 1, 0, 0};
int out_dc[5] = {0, 1, 0, -1, 0};
bool check_out(pair<int, int> standard) {

    for (int k = 0; k < 5; k++) {
        int nxt_r = standard.first + out_dr[k];
        int nxt_c = standard.second + out_dc[k];

        if (nxt_r < 4 || nxt_r > R +3 || nxt_c < 1 || nxt_c > C) {
            return false;
        }

    }

    return true;
}

int main() {

    cin >> R >> C >> T;
    // arr 초기화
    for (int i = 0; i < 74; i++) {
        for (int j = 0; j < 74; j++) {
            arr[i][j] = 0;
        }
    }

    for (int test_case = 1; test_case <= T; test_case++) {

        int cin_c, cin_d;
        cin >> cin_c >> cin_d;

        Robot robot = Robot(cin_c, cin_d);
        robots[test_case] = robot;

    }

    int answer = 0;
    for (int test_case = 1; test_case <= T; test_case++) {

        Robot& robot = robots[test_case];

        /*cout << "test_case : " << test_case << "\n";
        for (int i = 4; i <= R+3; i++) {
            for (int j = 1; j <= C; j++) {
                cout << arr[i][j] << " ";
            }
            cout << "\n";
        }*/

        // 최대한 내려가기
        while (true) {

            /*cout << "test_case : "<< test_case << endl;
for (int i = 0; i < 5; i++) {
    cout << "r : "  << robot.pos[i].first << " c : " << robot.pos[i].second << "\n";
}*/

            // 1. 아래로 내려갈 수 있는지 체크
            if (check_down(robot.pos[2])) {

                //cout << "down";

                robot.move_bottom();
                continue;
            }

            // 2. 서쪽으로 갈 수 있는지 체크
            if (check_left(robot.pos[3])) {

                //cout << "left";
                robot.move_left();
                continue;
            }

            // 3. 동쪽으로 갈 수 있는지 체크
            if (check_right(robot.pos[1])) {

                //cout << "right";
                robot.move_right();
                continue;
            }

            // 전부 안 되면 이동 종료
            break;
        }


        // 격자 밖으로 넘어갔는지 체크
        if (!check_out(robot.pos[4])) {

            // 넘어갔으면 전체 0으로 초기화 후 다음으로 이동
            for (int i = 0; i < 74; i++) {
                for (int j = 0; j < 74; j++) {
                    arr[i][j] = 0;
                }
            }

            continue;
        }

        // arr 채우기
        for (int i = 0; i < 5; i++) {
            arr[robot.pos[i].first][robot.pos[i].second] = test_case;
        }

        queue<pair<int, int>> q;
        bool visited[74][74];
        for (int i = 0; i < 74; i++) {
            for (int j = 0; j < 74; j++) {
                visited[i][j] = false;
            }
        }

        q.push(robot.pos[4]);
        visited[robot.pos[4].first][robot.pos[4].second] = true;
        //cout << "test_case 의 d : " << robots[test_case].d << "\n";



        while (!q.empty()) {

            auto cur = q.front();
            q.pop();
            int cur_robot_d = robots[arr[cur.first][cur.second]].d;

            for (int k = 0; k < 4; k++) {
                int nxt_r = cur.first + dr[k];
                int nxt_c = cur.second + dc[k];

                // 격자 밖으로 넘어가면 이동 x
                if (nxt_r < 4 || nxt_r > R+3 || nxt_c < 1 || nxt_c > C) {
                    continue;
                }

                // 이미 방문 했으면 이동 x
                if (visited[nxt_r][nxt_c]) {
                    continue;
                }

                // 로봇이 없으면 이동 x
                if (arr[nxt_r][nxt_c] == 0) {
                    continue;
                }

                // 다음으로 이동할 수 있는지 체크
                if (arr[cur.first][cur.second] == arr[nxt_r][nxt_c]) {

                    // 번호가 같으면 로직 o
                    q.push({nxt_r, nxt_c});
                    visited[nxt_r][nxt_c] = true;

                }else if (arr[cur.first][cur.second] != arr[nxt_r][nxt_c]  && robots[arr[cur.first][cur.second]].pos[cur_robot_d] == make_pair(cur.first, cur.second)) {

                    // 번호가 달라도 이전 노드가 출구 였다면
                    q.push({nxt_r, nxt_c});
                    visited[nxt_r][nxt_c] = true;
                }

            }
        }

        int result_r = -1;
        int result_c = -1;
        for (int i = 4; i <= R+3; i++) {
            for (int j = 1; j <= C; j++) {
                if (visited[i][j]) {
                    if (i > result_r) {
                        result_r = i;
                        result_c = j;
                    }
                    //result_r = max(result_r, i);
                }
            }
        }

        //cout << "result_r : " << result_r - 3 << "result_c : " << result_c <<  "\n";

        answer += (result_r - 3);
    }

    /*cout << "\n";
    for (int i = 4; i <= R+3; i++) {
        for (int j = 1; j <= C; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }*/


    cout << answer << "\n";

}