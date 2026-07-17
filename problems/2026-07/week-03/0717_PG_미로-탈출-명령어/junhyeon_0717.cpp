//
// Created by 임준현 on 26. 7. 16.
//

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

// 상태 저장 구조체
struct node {

    int r;
    int c;
    int cnt;
    string str;

    node(int r, int c, int cnt, string str) {
        this->r = r;
        this->c = c;
        this->cnt = cnt;
        this->str = str;
    }
};

// 사전 순 으로 이동하도록 배열 설정
int dx[4] = {0, -1, 1, 0};
int dy[4] = {1, 0, 0, -1};
string dstr[4] = {"d", "l", "r", "u"};

// 메모리 이슈 고려해 전역 변수로 설정
queue<node> q;


// 문제1: 처음에 visited을 안 두고 전부 queue에 저장했는데 시간 초과 뜸 -> 중복된 좌표(사전 순이 낮은 좌표)는 queue에 넣지 않고 사전에 거르자!
// cnt 번째 때 넣을 좌표가 중복되는지 검사하는 set 설정
unordered_set<int> visited[2502];
// 문제2: 처음에 크기를 2501로 설정 -> segment 에러 -> 2502로 설정해야 함
// -> 이전 단계에 다음 단계 확인 후 visited에 넣으니 +1 여유 => 배열 밖 검사를 고려하고 안전하게 배열은 여유있게 크기 설정하자!


string solution(int n, int m, int x, int y, int r, int c, int k) {

    // r, c , cnt(몇 번째 인지), string(문자열)
    q.push(node(x, y, 0, ""));

    // 0번째에 r,c 가 이미 후보군에 있음을 표시
    // 100*r + c 형태로 좌표를 하나의 변수로 치환
    visited[0].insert(100*x + y);

    while (!q.empty()) {

        node cur = q.front();
        q.pop();

        // 조건에 맞으면 해당 문자열 바로 반환
        if (cur.cnt == k) {
            if (cur.r == r && cur.c == c) {
                return cur.str;
            }
        }

        // 조건에 맞는 게 없고 다음 i 로 넘어갔으므로 바로 종료
        if (cur.cnt > k) {
            return "impossible";
        }

        for (int i = 0; i < 4; i++) {
            int nxt_r = cur.r + dy[i];
            int nxt_c = cur.c + dx[i];

            // 갈 수 있는지 조건 검사
            if (nxt_r < 1 || nxt_c < 1 || nxt_r > n || nxt_c > m) {
                continue;
            }

            // 다음 값 설정(몇 번째인지, 문자열)
            int nxt_cnt = cur.cnt + 1;
            string nxt_str = cur.str + dstr[i];

            // 만약 nxt_cnt 번째에 해당 queue로 가는 좌표가 있을 경우 굳이 또 넣지 않기 (이미 사전 순대로 넣어짐 -> 가장 사전 순 높은 거 하나만 queue에 저장)
            if (visited[nxt_cnt].find(nxt_r * 100 + nxt_c) != visited[nxt_cnt].end()) {
                continue;
            }

            q.push(node(nxt_r, nxt_c, nxt_cnt, nxt_str));
            visited[nxt_cnt].insert(nxt_r * 100 + nxt_c);

        }
    }
    return "impossible";

}