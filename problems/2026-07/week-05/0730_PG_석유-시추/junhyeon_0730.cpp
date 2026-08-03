//
// Created by 임준현 on 26. 7. 30.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int n;
int m;
int arr[501][501];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int solution(vector<vector<int>> land) {

    int n = land.size();
    int m = land[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][i] = 0;
        }
    }

    queue<pair<int, int>> q;
    int number = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // 석유가 있는지 검사, 석유가 없으면 건너뛰기
            if (land[i][j] == 0) {
                continue;
            }

            // 이미 방문했는지 검사, 방문했으면 건너뛰기
            if (arr[i][j] != 0) {
                continue;
            }

            // 새로운 석유 공간 -> 새로운 번호 부여
            int now_number = number;
            number++;

            // 해닥 석유 공간에 대해 bfs 시작
            q.push(make_pair(i, j));
            arr[i][j] = now_number;

            while (!q.empty()) {

                auto cur = q.front();
                q.pop();

                for (int k = 0; k < 4; k++) {
                    int new_r = cur.first + dr[k];
                    int new_c = cur.second + dc[k];

                    if (new_r < 0 || new_r >= n || new_c < 0 || new_c >=m ) {
                        continue;
                    }

                    // 석유가 있는지 검사, 석유가 없으면 건너뛰기
                    if (land[new_r][new_c] == 0) {
                        continue;
                    }

                    if (arr[new_r][new_c] != 0) {
                        continue;
                    }

                    q.push(make_pair(new_r, new_c));
                    arr[new_r][new_c] = now_number;
                }

            }
        }
    }

    int answer = 0;
    unordered_map<int, int> um;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (um.find(arr[i][j]) == um.end()) {
                um[arr[i][j]] = 1;
            }else {
                um[arr[i][j]]++;
            }
        }
    }


    for (int j = 0; j <m; j++) {
        unordered_set<int> us;
        int cnt = 0;

        for (int i = 0; i < n; i++) {

            if (arr[i][j] == 0) {
                continue;
            }

            if (us.find(arr[i][j]) != us.end()) {
                continue;
            }

            us.insert(arr[i][j]);
            cnt += um[arr[i][j]];

        }

        answer = max(answer, cnt);
    }


    return answer;


}