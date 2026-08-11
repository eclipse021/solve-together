#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[500][500] = {0};

int solution(vector<vector<int>> triangle) {

    dp[0][0] = triangle[0][0];
    int answer = dp[0][0];

    for(int i = 1; i<triangle.size(); i++){
        for(int j = 0; j <= i; j++){
            if(j == 0){
                dp[i][j] = dp[i-1][j] + triangle[i][j];
                continue;
            }

            if(j == i){
                dp[i][j] = dp[i-1][j-1] + triangle[i][j];
                continue;
            }

            dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j];
        }
    }

    for(int j = 0; j < triangle.size(); j++){
        answer = max(answer, dp[triangle.size()-1][j]);
    }


    return answer;
}