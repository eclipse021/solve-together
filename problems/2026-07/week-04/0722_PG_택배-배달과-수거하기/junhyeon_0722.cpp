//
// Created by 임준현 on 26. 7. 22.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

#define ll long long

using namespace std;

struct cmp {
    bool operator()(const pair<ll, ll>& a, const pair<ll, ll>& b) {
        return a.first < b.first;
    }
};

ll max_value(ll a, ll b) {
    if (a > b) {
        return a;
    }
    return b;
}

priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> deliver_pq;
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, cmp> pick_pq;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {

    for (ll i = 0; i<deliveries.size(); i++) {
        if (deliveries[i] == 0) {
            continue;
        }

        deliver_pq.push(make_pair(i+1, deliveries[i]));
    }

    for (ll i = 0; i<pickups.size(); i++) {
        if (pickups[i] == 0) {
            continue;
        }

        pick_pq.push(make_pair(i+1, pickups[i]));
    }

    ll answer = 0;

    while (true) {

        if (deliver_pq.empty() && pick_pq.empty()) {
            break;
        }

        // 배달하면서 수거하기
        ll new_cap = 0;
        vector<pair<ll, ll>> new_deliveries;

        while (!deliver_pq.empty()) {

            auto cur = deliver_pq.top();
            deliver_pq.pop();
            new_deliveries.push_back(cur);

            if (new_cap + cur.second > cap) {
                new_cap = cap;
                break;
            }

            new_cap += cur.second;

        }

        ll deliver_dist = 0;
        if (new_deliveries.size() > 0) {
            deliver_dist = new_deliveries[0].first;
        }

        for (auto cur : new_deliveries) {

            if (cur.second > new_cap) {
                deliver_pq.push(make_pair(cur.first, cur.second - new_cap));
                break;
            }

            new_cap -= cur.second;
        }

        new_cap = 0;
        vector<pair<ll, ll>> new_pickups;

        while (!pick_pq.empty()) {

            auto cur = pick_pq.top();
            pick_pq.pop();
            new_pickups.push_back(cur);

            if (new_cap + cur.second > cap) {
                new_cap = cap;
                break;
            }

            new_cap += cur.second;
        }

        ll pick_dist = 0;
        if (new_pickups.size() > 0) {
            pick_dist = new_pickups[0].first;
        }

        for (auto cur : new_pickups) {

            if (cur.second > new_cap) {
                pick_pq.push(make_pair(cur.first, cur.second - new_cap));
                break;
            }

            new_cap -= cur.second;
        }

        answer += max_value(deliver_dist, pick_dist) * 2;
    }


    return answer;
}