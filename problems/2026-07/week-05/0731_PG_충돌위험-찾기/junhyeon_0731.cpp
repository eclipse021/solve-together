//
// Created by 임준현 on 26. 7. 27.
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

vector<vector<int>> overall_points;
int answer;

// 로봇 구조체
// 현재 위치, 현재 목표, 목표 리스트, 완료 여부 저장
struct robot {

    int now_r;
    int now_c;
    int now_target_index;
    vector<int> target_list;
    bool finished;

    robot(vector<int> target_list) {
        this->now_r = -1;
        this->now_c = -1;
        this->now_target_index = 0;

        this->target_list = target_list;
        this->finished = false;
    }

};

// 모듯 로봇 정보 저장
vector<robot> robots;

// 맨 처음 세팅 메서드
// 가장 첫 번째 목표를 로봇 현재 위치로 설정 및 시작점에서 겹치는 횟수 answer에 추가
void setting_robots() {

    unordered_map<int, int> um;

    // 세팅
    for (int i = 0; i < robots.size(); i++) {

        if (robots[i].finished) {
            continue;
        }

        // 첫번째 위치에 로봇 위치 두기
        int target_index = robots[i].now_target_index;
        robots[i].now_target_index += 1;

        int target_location = robots[i].target_list[target_index];

        // 첫번째 목표의 r -> now_r , c -> now_c
        robots[i].now_r = overall_points[target_location][0];
        robots[i].now_c = overall_points[target_location][1];

        int key = robots[i].now_r * 1000 + robots[i].now_c;
        if (um.find(key) == um.end()) {
            um[key] = 1;
        }else {
            um[key]++;
        }
    }

    // 검사
    for (auto m : um) {
        if (m.second > 1) {
            //cout << "r : " << m.first / 1000 << " c : " << m.second % 1000 << endl;

            answer++;
        }
    }
}

// 로봇 이동 메서드
// 이동해야 할 위치로 로봇 위치 재설정 및 해당 위치에 겹치는 횟수로 answer 추가
void moving_robots() {

    unordered_map<int, int> um;

    // 세팅
    for (int i = 0; i < robots.size(); i++) {

        if (robots[i].finished) {
            continue;
        }

        int target_index = robots[i].now_target_index;
        int target_location = robots[i].target_list[target_index];

        int target_r = overall_points[target_location][0];
        int target_c = overall_points[target_location][1];

        int now_r = robots[i].now_r;
        int now_c = robots[i].now_c;


        int min_r;
        int min_c;

        if (now_r != target_r) {

            if (now_r < target_r) {
                min_r = now_r + 1;
                min_c = now_c;
            }else {
                min_r = now_r - 1;
                min_c = now_c;
            }
        }else {

            if (now_c < target_c) {
                min_c = now_c + 1;
                min_r = now_r;
            }else {
                min_c = now_c - 1;
                min_r = now_r;
            }

        }

        //cout << "로봇 번호 : " << i << " 원래 r: " << now_r << " c: " <<now_c << " 타겟 r: " << target_r << " c: " << target_c  <<" 이동할 r: "<< min_r << " c: "<< min_c << endl;

        // row, col 변경
        robots[i].now_r = min_r;
        robots[i].now_c = min_c;


        // 목표 위치에 도달했을 때
        if (min_r == target_r && min_c == target_c) {

            // 마지막 목표일 때 -> 해당 로봇 구조체의 완료 상태를 true로 변경
            if (target_index == robots[i].target_list.size() - 1) {
                robots[i].finished = true;
            }else { // 다음 목표가 존재 할 때 -> 목표를 다음 목표로 이동
                robots[i].now_target_index += 1;
            }

        }


        int key = robots[i].now_r * 1000 + robots[i].now_c;
        //cout << "key: " << key << "\n";
        if (um.find(key) == um.end()) {
            um[key] = 1;
        }else {
            um[key]++;
        }
    }

    // 검사
    for (auto m : um) {
        if (m.second > 1) {
            //cout << "r : " << m.first / 1000 << " c : " << m.second % 1000 << endl;
            answer++;
        }
    }

}

int solution(vector<vector<int>> points, vector<vector<int>> routes) {

    vector<int> v;
    overall_points.push_back(v); // 0번 인덱스에 의미없는 값 추가
    for (vector<int> point : points) {
        overall_points.push_back(point);
    }

    // 모든 로봇에 좌표 부여
    for (vector<int>& route : routes) {

        robot r = robot(route);
        robots.push_back(r);

    }

    answer = 0;

    // 0. 로봇 세팅
    setting_robots();


    while (true) {

        int now_finish_robot_cnt = 0;
        for (int i = 0; i < robots.size(); i++) {
            if (robots[i].finished) {
                now_finish_robot_cnt++;
            }
        }

        // 1. 전부 다 통과했는지 검사 -> 전부 다 완료했으면 answer 리턴 후 종료
        if (now_finish_robot_cnt == robots.size()) {
            return answer;
        }

        // 2. 최단 거리 이동
        moving_robots();

    }
}