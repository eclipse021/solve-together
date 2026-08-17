import java.util.*;

class Solution {

    static class Node{

        int r;
        int c;
        int cnt;

        Node(int r, int c, int cnt){
            this.r = r;
            this.c = c;
            this.cnt = cnt;
        }

    }

    static class pair{
        int first;
        int second;

        pair(int first, int second){
            this.first = first;
            this.second = second;
        }
    }

    static final int INF = 2100000000;
    static String[][] arr = new String[101][101]; // arr[101][101] x
    static int[][] visited = new int[101][101]; // visited[101][101] x

    public int solution(String[] board) {

        pair start = null;  // 객체는 처음에는 Null 로 지정
        pair target = null; // 객체는 처음에는 Null로 지정

        // arr 초기화
        for(int i = 0; i < board.length; i++){
            for(int j = 0; j < board[i].length(); j++){

                String str = board[i].substring(j, j+1);

                if(str.equals("R")){
                    start = new pair(i, j); // new 필수
                    arr[i][j] = ".";
                    continue;
                }

                if(str.equals("G")){
                    target = new pair(i, j); // new 필수
                    arr[i][j] = ".";
                    continue;
                }

                arr[i][j] = str;
            }
        }

        // visited 초기화
        int n = board.length;
        int m = board[0].length();

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                visited[i][j] = INF;
            }
        }

        int[] dr = {-1, 0, 1, 0};
        int[] dc = {0, 1, 0, -1};

        Node node = new Node(start.first, start.second, 0);
        visited[start.first][start.second] = 0;

        Queue<Node> q = new ArrayDeque<>(); // queue는 new ArrayDeque<>() 필수
        q.offer(node);

        while(!q.isEmpty()){ // empty() x -> isEmpty()

            Node cur = q.peek();
            q.poll();

            for(int k = 0; k < 4; k++){

                int next_r = cur.r + dr[k];
                int next_c = cur.c + dc[k];

                while(true){

                    if(next_r < 0 || next_r >= n || next_c < 0 || next_c >=m)                     {
                        break;
                    }

                    if(arr[next_r][next_c].equals("D")){
                        break;
                    }

                    next_r += dr[k];
                    next_c += dc[k];

                }

                next_r -= dr[k];
                next_c -= dc[k];

                if(visited[next_r][next_c] != INF){
                    continue;
                }

                visited[next_r][next_c] = cur.cnt + 1;

                Node nxt = new Node(next_r, next_c, cur.cnt+1); // 객체 생성은 new 필수
                q.offer(nxt);

            }
        }

        if(visited[target.first][target.second] == INF){
            return -1;
        }else{
            return visited[target.first][target.second];
        }

    }
}