import java.util.*;

class Solution {

    static List<Integer>[] adj = new ArrayList[1000001];


    public int[] solution(int[][] edges) {

        for(int i = 0; i < 1000001; i++){
            adj[i] = new ArrayList<>();
        }

        for(int[] edge : edges){
            adj[edge[0]].add(edge[1]);
        }

        // 생성한 정점 번호 찾기
        int specific = 0;

        boolean[] isSpecific = new boolean[1000001];

        // 1. 초기화
        for(int i = 1 ; i < 1000001; i++){
            isSpecific[i] = true;
        }

        // 2-1. 조건 1) 나가는 정점 개수가 2개 이상 필수
        for(int i = 1; i < 1000001; i++){
            if(adj[i].size() < 2){
                isSpecific[i] = false;
            }
        }

        // 2-2. 조건 2) 들어오는 정점이 존재하면 안 됨
        for(int i = 1; i < 1000001; i++){

            for(int a : adj[i]){
                isSpecific[a] = false;
            }
        }

        // 2-3. 위 두 조건을 통과한 값을 생성한 정점 번호로 지정
        for(int i = 1; i < 1000001; i++){

            if(isSpecific[i]){
                specific = i;
                break;
            }
        }

        //System.out.println("specific : " + specific);

        int donutCnt = 0;
        int barCnt = 0;
        int eightCnt = 0;

        // 3. 각 그래프 개수 찾기
        for(int start : adj[specific]){

            Set<Integer> visited = new HashSet<>();
            Queue<Integer> q = new ArrayDeque<>();

            // adj 크기가 2 이상이 존재하면 8자 그래프
            boolean is_eight = false;
            // visited에 겹치는게 없었으면 막대 그래프
            boolean is_bar = true;

            q.offer(start);
            visited.add(start);

            while(!q.isEmpty()){

                int cur = q.peek();
                q.poll();

                for(int nxt : adj[cur]){

                    // System.out.println("nxt : " + nxt);

                    if(adj[nxt].size() >= 2){
                        is_eight = true;
                    }

                    if(visited.contains(nxt)){
                        is_bar = false;
                        continue;
                    }

                    visited.add(nxt);
                    q.offer(nxt);

                }
            }

            if(is_bar){
                //System.out.println("start : " + start + ", 막대 모양");
                barCnt++;
                continue;
            }

            if(is_eight){
                //System.out.println("start : " + start + ", 8자 모양");
                eightCnt++;
                continue;
            }

            //System.out.println("start : " + start + ", 도넛 모양");
            donutCnt++;
        }

        int[] answer = {specific, donutCnt, barCnt, eightCnt};
        return answer;
    }
}