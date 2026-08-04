//
// Created by 임준현 on 26. 8. 4.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>

#define ll long long

using namespace std;

bool cmp(ll a, ll b) {
    return a > b;
}

void make_number(set<ll>& us, deque<char>& dq) {

    int dq_size = dq.size();
    ll weight = 1;
    ll sum = 0;

    for (int i = dq_size - 1; i >=0 ; i--) {

        char c;
        if (dq[i] <= '9') {
            c = dq[i] - '0';
        }else {
            c = dq[i] - 'A' + 10;
        }

        sum += c * weight;
        weight *= 16;

    }

    us.insert(sum);

}

int main() {

    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++) {

        int N, K;
        cin >> N >> K;

        deque<char> dq[4];
        int n_size = N/4;

        for (int i = 0; i < N; i++) {

            char x;
            cin >> x;

            int dq_number = i / n_size;
            dq[dq_number].push_back(x);
        }

        set<ll> us;

        // 맨 처음
        for (int i = 0; i < 4; i++) {
            make_number(us, dq[i]);
        }

        for (int rotate = 0; rotate < n_size; rotate++) {

            for (int i = 0; i < 4; i++) {
                int now_dq = i;
                int next_dq = (i + 1) % 4;

                char end_now_dq = dq[now_dq].back();

                dq[now_dq].pop_back();
                dq[next_dq].push_front(end_now_dq);

            }

            for (int i = 0; i < 4; i++) {
                make_number(us, dq[i]);
            }

        }

        vector<ll> v;
        for (ll n : us) {
            v.push_back(n);
        }
        sort(v.begin(), v.end(), cmp);

        cout << "#" << test_case << " " << v[K - 1] << "\n";


    }


}