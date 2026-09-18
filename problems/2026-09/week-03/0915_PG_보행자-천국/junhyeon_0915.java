import java.util.*;

class Solution {
    int MOD = 20170805;
    int[][][] cnt = new int[500][500][2];

    // 0: 오른쪽으로 이동, 1: 아래로 이동
    int[] dr = {0, 1};
    int[] dc = {1, 0};

    static class Node{
        int r;
        int c;

        Node(int r, int c){
            this.r = r;
            this.c = c;
        }
    }

    boolean[][] visited = new boolean[500][500];

    public int solution(int m, int n, int[][] cityMap) {

        // m -> r, n -> c

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < 2; k++){
                    cnt[i][j][k] = 0;
                }
                visited[i][j] = false;
            }
        }

        cnt[0][0][0] = 1;

        Queue<Node> q = new ArrayDeque<>();
        q.offer(new Node(0, 0));
        visited[0][0] = true;

        while(!q.isEmpty()){

            Node cur = q.peek();
            q.poll();

            // 오른쪽으로 이동할 수 있는지
            int nxt_r = cur.r + dr[0];
            int nxt_c = cur.c + dc[0];

            // 범위 밖이 아닌지
            if(nxt_r >= 0 && nxt_r <= m-1 && nxt_c >= 0 && nxt_c <= n-1){

                // 보행 금지 표지 판이 아닌지
                if(cityMap[nxt_r][nxt_c] != 1){

                    // 원래 방향이면 무조건 cnt에 추가
                    cnt[nxt_r][nxt_c][0] += cnt[cur.r][cur.c][0] % MOD;

                    // 만약 이 전이 회전금지 표지판이었다면 방향 변경 검사 후 cnt에 추가
                    if(cityMap[cur.r][cur.c] != 2){
                        cnt[nxt_r][nxt_c][0] += cnt[cur.r][cur.c][1] % MOD;
                    }

                }

                if(!visited[nxt_r][nxt_c]){
                    q.offer(new Node(nxt_r, nxt_c));
                    visited[nxt_r][nxt_c] = true;
                }
            }


            // 아래쪽으로 이동할 수 있는지
            nxt_r = cur.r + dr[1];
            nxt_c = cur.c + dc[1];

            // 범위 밖이 아닌지
            if(nxt_r >= 0 && nxt_r <= m-1 && nxt_c >= 0 && nxt_c <= n-1){

                // 보행 금지 표지 판이 아닌지
                if(cityMap[nxt_r][nxt_c] != 1){

                    // 원래 방향이면 무조건 cnt에 추가
                    cnt[nxt_r][nxt_c][1] += cnt[cur.r][cur.c][1] % MOD;

                    // 만약 이 전이 회전금지 표지판이었다면 방향 변경 검사 후 cnt에 추가
                    if(cityMap[cur.r][cur.c] != 2){
                        cnt[nxt_r][nxt_c][1] += cnt[cur.r][cur.c][0] % MOD;
                    }
                }

                if(!visited[nxt_r][nxt_c]){
                    q.offer(new Node(nxt_r, nxt_c));
                    visited[nxt_r][nxt_c] = true;
                }
            }
        }

        int answer = (cnt[m-1][n-1][0] + cnt[m-1][n-1][1]) % MOD;
        return answer;
    }
}