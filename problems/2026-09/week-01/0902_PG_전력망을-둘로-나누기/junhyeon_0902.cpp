#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> arr[101];

int solution(int n, vector<vector<int>> wires) {

    int answer = n;


    for(auto wire : wires){

        arr[wire[0]].push_back(wire[1]);
        arr[wire[1]].push_back(wire[0]);

    }

    for(auto wire : wires){

        bool visited[101];
        for(int i = 0; i < 101; i++){
            visited[i] = false;
        }

        queue<int> q;
        q.push(wire[0]);
        visited[wire[0]] = true;

        int cnt = 1;
        while(!q.empty()){

            int cur = q.front();
            q.pop();

            for(int nxt : arr[cur]){

                if(cur == wire[0] && nxt == wire[1]){
                    continue;
                }

                if(cur == wire[1] && nxt == wire[0]){
                    continue;
                }

                if(visited[nxt]){
                    continue;
                }

                q.push(nxt);
                visited[nxt] = true;
                cnt++;

            }
        }

        answer = min(answer, abs(n - 2 * cnt));
    }
    return answer;
}