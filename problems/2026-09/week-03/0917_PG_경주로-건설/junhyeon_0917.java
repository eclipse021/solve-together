import java.util.*;

class Solution {

    static class Node{

        int r;
        int c;
        int dir;
        int cost;

        Node(int r, int c, int dir, int cost){
            this.r = r;
            this.c = c;
            this.dir = dir;
            this.cost = cost;
        }
    }

    static int[] dr = {0, 1, 0, -1};
    static int[] dc = {1, 0, -1, 0};

    public int solution(int[][] board) {

        PriorityQueue<Node> pq = new PriorityQueue<>(
                (a,b) -> Integer.compare(a.cost, b.cost)
        );

        int n = board.length;

        int[][][] dist = new int[n][n][4];

        final int INF = 2100000000;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < 4; k++){
                    dist[i][j][k] = INF;
                }
            }
        }

        pq.offer(new Node(0, 0, 4, 0));

        while(!pq.isEmpty()){

            Node cur = pq.poll();

            if(cur.dir != 4 && cur.cost != dist[cur.r][cur.c][cur.dir]){
                continue;
            }

            for(int k = 0; k < 4; k++){

                int nxt_r = cur.r + dr[k];
                int nxt_c = cur.c + dc[k];

                if(nxt_r < 0 || nxt_r >= n || nxt_c < 0 || nxt_c >= n){
                    continue;
                }

                if(board[nxt_r][nxt_c] == 1){
                    continue;
                }

                int nxt_dist;

                if(cur.dir == k || cur.dir == 4){
                    nxt_dist = cur.cost + 100;
                }else{
                    nxt_dist = cur.cost + 600;
                }

                if(nxt_dist < dist[nxt_r][nxt_c][k]){

                    pq.offer(new Node(nxt_r, nxt_c, k, nxt_dist));
                    dist[nxt_r][nxt_c][k] = nxt_dist;
                }
            }
        }

        int answer = INF;

        for(int k = 0; k < 4; k++){
            answer = Math.min(answer, dist[n-1][n-1][k]);
        }

        return answer;
    }
}