//
// Created by 임준현 on 26. 8. 6.
//
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct cmp {

    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
    }

};

vector<int> solution(vector<int> numbers) {

    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    vector<int> answer(numbers.size(), -1);

    for (int i = 0; i < numbers.size(); i++) {

        if (pq.empty()) {
            pq.push(make_pair(numbers[i], i));
            continue;
        }

        while (!pq.empty() && pq.top().first < numbers[i]) {
            auto cur = pq.top();
            pq.pop();

            answer[cur.second] = numbers[i];
        }

        pq.push(make_pair(numbers[i], i));

    }

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        answer[cur.second] = -1;
    }

    return answer;
}