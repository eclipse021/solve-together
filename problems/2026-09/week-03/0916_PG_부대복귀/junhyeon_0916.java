import java.util.*;

class Solution {
    public int[] solution(int n, int[][] roads, int[] sources, int destination) {

        int[] dist = new int[100001];
        for(int i = 0; i <=n; i++){
            dist[i] = -1;
        }

        List<Integer>[] list = new ArrayList[100001];
        for(int i = 0; i <=n; i++){
            list[i] = new ArrayList<>();
        }

        for(int i = 0; i < roads.length; i++){
            list[roads[i][0]].add(roads[i][1]);
            list[roads[i][1]].add(roads[i][0]);
        }

        Queue<Integer> q = new ArrayDeque<>();
        q.offer(destination);
        dist[destination] = 0;

        while(!q.isEmpty()){

            int cur = q.peek();
            q.poll();

            for(int nxt : list[cur]){

                if(dist[nxt] != -1){
                    continue;
                }

                dist[nxt] = dist[cur] + 1;
                q.offer(nxt);

            }
        }

        List<Integer> answerList = new ArrayList<>();
        for(int s : sources){
            answerList.add(dist[s]);
        }

        int[] answer = new int[answerList.size()];
        for(int i = 0; i < answerList.size(); i++){
            answer[i] = answerList.get(i);
        }

        return answer;
    }
}