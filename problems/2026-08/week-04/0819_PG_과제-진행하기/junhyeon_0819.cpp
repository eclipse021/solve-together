//
// Created by 임준현 on 26. 8. 19.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

struct homework {

    string name;
    int start;
    int playtime;

    homework(string name, int start, int playtime) {
        this->name = name;
        this->start = start;
        this->playtime = playtime;
    }
};

bool vc_cmp(const homework& a, const homework& b) {
    return a.start < b.start;
}



int time2int(string str) {

    int i0 = str[0] - '0';
    int i1 = str[1] - '0';

    int i3 = str[3] - '0';
    int i4 = str[4] - '0';

    return (i0 * 10 + i1) * 60 + i3 * 10 + i4;

}

vector<string> solution(vector<vector<string>> plans) {

    vector<string> answer;

    vector<homework> todo_homework;
    for (vector<string>& plan : plans) {
        homework h = homework(plan[0], time2int(plan[1]), stoi(plan[2]));
        todo_homework.push_back(h);
    }

    sort(todo_homework.begin(), todo_homework.end(), vc_cmp);

    stack<homework> st;
    int now_todo_index = 0;

    for (int time = 0; time <= 1500000; time++) {

        if (now_todo_index == todo_homework.size() && st.empty()) {
            break;
        }

        if (!st.empty()) {

            auto cur = st.top();
            st.pop();

            if (cur.playtime != 1) {
                homework h = homework(cur.name, cur.start, cur.playtime - 1);
                st.push(h);
            }else {
                answer.push_back(cur.name);
            }

        }

        if (now_todo_index < todo_homework.size()) {
            if (todo_homework[now_todo_index].start == time) {
                st.push(todo_homework[now_todo_index]);
                now_todo_index++;
            }
        }
    }

    return answer;
}