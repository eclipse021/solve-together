import java.util.*;

class Solution {
    public long solution(int n, int[] works) {

        long[] cnt = new long[50001];
        for(int i = 0; i < 50001; i++){
            cnt[i] = 0;
        }

        // 각 작업 시간이 몇개인지 저장
        for(int w : works){
            cnt[w]++;
        }

        int index = 50000;
        while(index >= 1){

            if(cnt[index] <= n){

                n -= cnt[index];
                cnt[index-1] += cnt[index];
                cnt[index] = 0;

                index--;

            }else{

                cnt[index] -= n;
                cnt[index-1] += n;

                n = 0;
                break;

            }
        }

        long answer = 0;

        for(int i = 0; i < 50001; i++){
            answer = answer + (1L * i * i) * cnt[i];
        }

        return answer;
    }
}