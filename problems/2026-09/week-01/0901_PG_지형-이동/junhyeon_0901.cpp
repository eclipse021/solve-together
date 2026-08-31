#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

pair<int,int> parent[300][300];

pair<int, int> find(pair<int,int> x){

    if(parent[x.first][x.second] == make_pair(-1, -1)){
        return x;
    }

    return parent[x.first][x.second] = find(parent[x.first][x.second]);

}

bool uni(pair<int, int> u, pair<int, int> v ){

    u = find(u);
    v = find(v);

    if(u == v){
        return false;
    }

    parent[v.first][v.second] = u;
    return true;

}

vector<vector<int>> o_land;

struct node{

    pair<int, int> prev;
    pair<int, int> next;
    int dist;

    node(pair<int, int> prev, pair<int, int> next){
        this->prev = prev;
        this->next = next;

        dist = abs(o_land[prev.first][prev.second] - o_land[next.first][next.second]);
    }

};

bool cmp(node a, node b){
    return a.dist < b.dist;
}

int solution(vector<vector<int>> land, int height) {

    o_land = land;
    int n = land.size();
    int m = land[0].size();

    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < m; j++){
            parent[i][j] = {-1, -1};
        }
    }

    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0 , -1};

    vector<node> n_list;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){

            for(int k = 0; k < 4; k++){

                int nxt_r = i + dr[k];
                int nxt_c = j + dc[k];

                if(nxt_r < 0 || nxt_r >= n || nxt_c < 0 || nxt_c >=m ){
                    continue;
                }

                n_list.push_back(node(make_pair(i, j), make_pair(nxt_r, nxt_c)));

            }
        }
    }

    sort(n_list.begin(), n_list.end(), cmp);

    int answer = 0;

    for(auto no : n_list){

        if(uni(no.prev, no.next)){

            if(no.dist > height){
                answer += no.dist;
            }
        }

    }

    return answer;
}