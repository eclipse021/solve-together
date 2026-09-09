import java.util.*;

class Solution {
    public int solution(int x, int y, int n) {

        int[] dp = new int[1000001];
        for(int i = 0; i < 1000001; i++){
            dp[i] = -1;
        }

        Queue<Integer> q = new ArrayDeque<>();
        q.offer(x);
        dp[x] = 0;

        while(!q.isEmpty()){

            int cur = q.peek();
            q.poll();

            int nxt = cur + n;
            if(nxt <= 1000000){
                if(dp[nxt] == -1){
                    dp[nxt] = dp[cur] + 1;
                    q.offer(nxt);
                }
            }

            nxt = cur * 2;
            if(nxt <= 1000000){
                if(dp[nxt] == -1){
                    dp[nxt] = dp[cur] + 1;
                    q.offer(nxt);
                }
            }

            nxt = cur * 3;
            if(nxt <= 1000000){
                if(dp[nxt] == -1){
                    dp[nxt] = dp[cur] + 1;
                    q.offer(nxt);
                }
            }

        }

        return dp[y];
    }
}