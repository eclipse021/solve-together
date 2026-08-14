//
// Created by 임준현 on 26. 8. 13.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

pair<int, int> medusa;
pair<int, int> medusa_home;
pair<int, int> park;

int arr[51][51];
int knights[51][51] = {0};
bool stone_area[51][51] = {false};

vector<pair<int, int>> short_dist[51][51];

int main() {

    int N, M; //  마을 크기, 전사 수
    cin >> N >> M;

    int in_r, in_c;
    cin >> in_r >> in_c;
    // 메두사 시작 지점
    medusa_home = make_pair(in_r, in_c);

    cin >> in_r >> in_c;
    // 메두사 종료 지점
    park = make_pair(in_r, in_c);

    // knights -> 해당 좌표에 전사가 몇명 있는지
    for (int i = 0; i < M; i++) {
        cin >> in_r >> in_c;

        knights[in_r][in_c]++;
    }

    // 도로 정보 업데이트
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x;
            cin >> x;

            arr[i][j] = x;
        }
    }

    // 0. 메두사 가장 짧은 동선 찾기
    bool visited[51][51] = {false};
    queue<pair<int, int>> q;

    visited[medusa_home.first][medusa_home.second] = true;
    q.push(medusa_home);

    int dr_m_move[4] = {-1, 1, 0, 0};
    int dc_m_move[4] = {0, 0, -1, 1};

    while (!q.empty()) {

        auto cur = q.front();
        q.pop();

        for (int k = 0; k < 4; k++) {
            int next_r = cur.first + dr_m_move[k];
            int next_c = cur.second + dc_m_move[k];

            if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                continue;
            }

            if (arr[next_r][next_c] == 1) {
                continue;
            }

            if (visited[next_r][next_c]) {
                continue;
            }

            vector<pair<int, int>> next_dist = short_dist[cur.first][cur.second];
            next_dist.push_back(make_pair(next_r, next_c));

            short_dist[next_r][next_c] = next_dist;
            visited[next_r][next_c] = true;
            q.push(make_pair(next_r, next_c));

        }
    }

    // 만약 공원까지 가는 경로가 존재하지 않으면
    if (short_dist[park.first][park.second].size() == 0) {
        cout << -1 << "\n";
        return 0;
    }

    // 공원까지 이동
    for (int test_case = 0; test_case < short_dist[park.first][park.second].size(); test_case++) {

        // 0. 변수 세팅
        int answer_move_dist = 0; // 전사들이 움직인 횟수 -> 정정 필요 -> 정정 완료
        int answer_change_stone = 0; // 돌로 변한 사람 수 -> 정정 필요
        int answer_attack_medusa = 0; // 메두사 공격한 사람 수

        // 돌 구역 초기화
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                stone_area[i][j] = false;
            }
        }

        // 1. 메두사 이동
        medusa = short_dist[park.first][park.second][test_case];

        if (medusa == park) {
            cout << 0 << "\n";
            return 0;
        }

        // 해당 칸의 기사들이 공격받고 소멸
        knights[medusa.first][medusa.second] = 0;


        int dr_m_see[4] = {-1, 1, 0, 0};
        int dc_m_see[4] = {0, 0, -1, 1};

        int dr_offset[4] = {0, 0, 1, 1};
        int dc_offset[4] = {1, 1, 0, 0};

        // 2. 모든 방향으로 메두사의 시선 후 가장 높은 시선 선택
        int temp_change_stone_cnt = -1;
        bool temp_stone_area [51][51];

        /*cout << "test_case : " << test_case << "\n";
        cout << "메두사 : " << medusa.first << " " << medusa.second << "\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << knights[i][j] << " ";
            }
            cout << "\n";
        }*/

        for (int k = 0; k < 4; k++) {
            int now_change_cnt = 0;
            bool now_stone_area[51][51] = {false};
            vector<pair<int, int>> now_stone_area_knights;

            int standard_r = medusa.first;
            int standard_c = medusa.second;
            int index = 0;

            // k 방향에 맞춰 90도로 모든 공간을 stone_area로 지정
            while (true) {
                standard_r += dr_m_see[k];
                standard_c += dc_m_see[k];
                index++;

                if (standard_r < 0 || standard_r >= N || standard_c < 0 || standard_c >= N) {
                    break;
                }

                now_stone_area[standard_r][standard_c] = true;
                if (knights[standard_r][standard_c] > 0) {
                    now_stone_area_knights.push_back(make_pair(standard_r, standard_c));
                }

                for (int i = 1; i <=index; i++) {
                    int next_r = standard_r + dr_offset[k] * i;
                    int next_c = standard_c + dc_offset[k] * i;

                    if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                        continue;
                    }

                    now_stone_area[next_r][next_c] = true;
                    if (knights[next_r][next_c] > 0) {
                        now_stone_area_knights.push_back(make_pair(next_r, next_c));
                    }
                }

                for (int i = 1; i <=index; i++) {

                    int next_r = standard_r + dr_offset[k] * i * (-1);
                    int next_c = standard_c + dc_offset[k] * i * (-1);

                    if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                        continue;
                    }

                    now_stone_area[next_r][next_c] = true;
                    if (knights[next_r][next_c] > 0) {
                        now_stone_area_knights.push_back(make_pair(next_r, next_c));
                    }

                }
            }

            // 가까운 방향 부터 석화 카운팅 및 뒤에 stone_area 해결
            for (auto cur : now_stone_area_knights) {

                if (!now_stone_area[cur.first][cur.second]) {
                    continue;
                }

                now_change_cnt += knights[cur.first][cur.second];
                standard_r = cur.first;
                standard_c = cur.second;
                index = 0;

                while (true) {

                    standard_r += dr_m_see[k];
                    standard_c += dc_m_see[k];
                    index++;

                    if (standard_r < 0 || standard_r >= N || standard_c < 0 || standard_c >= N) {
                        break;
                    }

                    now_stone_area[standard_r][standard_c] = false;

                    if (cur.first == medusa.first || cur.second == medusa.second) {
                        continue;
                    }

                    // 정정 필요
                    int origin_dist = (cur.first - medusa.first) * (cur.first - medusa.first)
                    + (cur.second - medusa.second) * (cur.second - medusa.second);

                    int temp_r = cur.first + dr_offset[k];
                    int temp_c = cur.second + dc_offset[k];
                    int temp_dist = (temp_r - medusa.first) * (temp_r - medusa.first)
                    + (temp_c - medusa.second) * (temp_c - medusa.second);

                    if (temp_dist > origin_dist) {
                        for (int i = 1; i <=index; i++) {
                            int next_r = standard_r + dr_offset[k] * i;
                            int next_c = standard_c + dc_offset[k] * i;

                            if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                                continue;
                            }

                            now_stone_area[next_r][next_c] = false;
                        }
                    }

                    temp_r = cur.first + dr_offset[k] * (-1);
                    temp_c = cur.second + dc_offset[k] * (-1);
                    temp_dist = (temp_r - medusa.first) * (temp_r - medusa.first)
                    + (temp_c - medusa.second) * (temp_c - medusa.second);

                    if (temp_dist > origin_dist) {
                        for (int i = 1; i <=index; i++) {

                            int next_r = standard_r + dr_offset[k] * i * (-1);
                            int next_c = standard_c + dc_offset[k] * i * (-1);

                            if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                                continue;
                            }

                            now_stone_area[next_r][next_c] = false;

                        }
                    }
                }
            }

            if (now_change_cnt > temp_change_stone_cnt) {
                temp_change_stone_cnt = now_change_cnt;

                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        temp_stone_area[i][j] = now_stone_area[i][j];
                    }
                }
            }
        }

        answer_change_stone = temp_change_stone_cnt;

        //cout << "test : " << test_case << "\n";
        //cout << "돌로 변한 영역 : \n";

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                stone_area[i][j] = temp_stone_area[i][j];
                // << stone_area[i][j] << " ";

            }
            //cout << "\n";
        }


        // 3. 전사들의 이동
        int temp_knights[51][51] = {0};
        int dr_k_m_first[4] = {-1, 1, 0, 0};
        int dc_k_m_first[4] = {0, 0, -1, 1};

        int dr_k_m_second[4] = {0, 0, -1, 1};
        int dc_k_m_second[4] = {-1, 1, 0, 0};


        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int final_r = i;
                int final_c = j;

                // 해당 자리에 기사가 없으면 skip
                if (knights[i][j] <= 0) {
                    continue;
                }

                // 돌로 돼서 못 움직이면 skip
                if (stone_area[i][j]) {

                    temp_knights[final_r][final_c] += knights[i][j];
                    continue;
                }

                int origin_dist = (final_r - medusa.first) * (final_r - medusa.first)
                + (final_c - medusa.second) * (final_c - medusa.second);

                bool is_possible = false;

                // 첫 번째 이동가능한지 체크
                for (int k = 0; k < 4; k++) {
                    int next_r = final_r + dr_k_m_first[k];
                    int next_c = final_c + dc_k_m_first[k];

                    // 격자 밖으로 나가면 안됨
                    if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                        continue;
                    }

                    // 시야 안으로 들어가면 안 됨
                    if (stone_area[next_r][next_c]) {
                        continue;
                    }

                    int next_dist = (next_r - medusa.first) * (next_r - medusa.first)
                    + (next_c - medusa.second) * (next_c - medusa.second);

                    if (next_dist < origin_dist) {
                        is_possible = true;
                        final_r = next_r;
                        final_c = next_c;

                        break;
                    }
                }

                // 갈 곳 없으면 그냥 넘어가기
                if (!is_possible) {
                    temp_knights[final_r][final_c] += knights[i][j];
                    continue;
                }

                is_possible = false;
                // 정정: origin_dist 재계산하기
                origin_dist = (final_r - medusa.first) * (final_r - medusa.first)
                + (final_c - medusa.second) * (final_c - medusa.second);

                // 두 번째로 이동가능한지 체크
                for (int k = 0; k < 4; k++) {

                    int next_r = final_r + dr_k_m_second[k];
                    int next_c = final_c + dc_k_m_second[k];

                    // 격자 밖으로 나가면 안됨
                    if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N) {
                        continue;
                    }

                    // 시야 안으로 들어가면 안 됨
                    if (stone_area[next_r][next_c]) {
                        continue;
                    }

                    int next_dist = (next_r - medusa.first) * (next_r - medusa.first)
                    + (next_c - medusa.second) * (next_c - medusa.second);

                    if (next_dist < origin_dist) {
                        is_possible = true;
                        final_r = next_r;
                        final_c = next_c;

                        break;
                    }
                }

                temp_knights[final_r][final_c] += knights[i][j];

                if (is_possible) {
                    answer_move_dist += 2 * knights[i][j];
                }else {
                    answer_move_dist += 1 * knights[i][j];
                }

            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                knights[i][j] = temp_knights[i][j];
            }
        }

        // 4. 메두사 공격
        answer_attack_medusa = knights[medusa.first][medusa.second];
        knights[medusa.first][medusa.second] = 0;


        cout << answer_move_dist << " " << answer_change_stone << " " << answer_attack_medusa << "\n";
    }

}