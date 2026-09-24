import java.util.*;

class Solution {

    public int solution(int n, int[] stations, int w) {

        int target = 1;
        int answer = 0;

        for(int i = 0; i < stations.length; i++){

            int now = stations[i] - w - 1;
            while(now >= target){

                answer++;
                now = now - (2*w + 1);

            }

            target = stations[i] + w + 1;

            if(i == stations.length - 1){

                target = n;
                now = stations[i] + w + 1;

                while(now <= target){

                    answer++;
                    now = now + (2*w + 1);
                }

            }
        }


        return answer;

    }
}