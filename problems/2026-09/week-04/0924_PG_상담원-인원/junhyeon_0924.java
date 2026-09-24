import java.util.*;


class Solution {

    static class Node{

        int startTime;
        int processTime;

        Node(int startTime, int processTime){
            this.startTime = startTime;
            this.processTime = processTime;
        }

    }

    static int answer = 2100000000;
    static int[][] result = new int[6][21];

    static void dfs(int index, int cnt, int value, int targetIndex, int targetCnt){

        if(index > targetIndex && cnt == targetCnt){
            answer = Math.min(answer, value);
            return;
        }

        if(cnt > targetCnt){
            return;
        }

        if(index > targetIndex){
            return;
        }

        for(int i = 1; i <= targetCnt; i++ ){

            dfs(index+1, cnt+i, value + result[index][i], targetIndex, targetCnt);
        }
    }

    public int solution(int k, int n, int[][] reqs) {

        List<Node>[] typeList = new ArrayList[k+1];

        // 1. 각 유형마다 List에 기록
        for(int i = 1; i <= k; i++){
            typeList[i] = new ArrayList<>();
        }

        for(int[] req : reqs){
            typeList[req[2]].add(new Node(req[0], req[1]));
        }


        // 2. 각 유형당 1~n 경우의 기다리는 시간 입력
        for(int index = 1; index <= k; index++){

            for(int cnt = 1; cnt <= n; cnt++){

                // 빨리 끝나는 노드 순으로 pq
                PriorityQueue<Integer> pq = new PriorityQueue<>(
                        (a,b) ->{
                            return Integer.compare(a,b);
                        }
                );

                int waitTime = 0;
                for(int i = 0; i < typeList[index].size(); i++){

                    if(i < cnt){

                        pq.offer(typeList[index].get(i).startTime
                                + typeList[index].get(i).processTime);
                        continue;
                    }

                    int prevTime = pq.peek();
                    pq.poll();

                    if(prevTime <= typeList[index].get(i).startTime){

                        pq.offer(typeList[index].get(i).startTime
                                + typeList[index].get(i).processTime);
                        continue;

                    }

                    waitTime += (prevTime - typeList[index].get(i).startTime);
                    pq.offer(prevTime + typeList[index].get(i).processTime);
                }

                result[index][cnt] = waitTime;
            }
        }

        dfs(1,0,0,k,n);

        return answer;
    }
}