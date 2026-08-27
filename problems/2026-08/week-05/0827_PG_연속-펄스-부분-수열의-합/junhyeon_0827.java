import java.util.*;

class Solution {
    public long solution(int[] sequence) {

        long max_value = 0;
        long now_value = 0;

        // 1 -1 1 ... 검사
        for (int i = 0; i < sequence.length; i++){

            if(i == 0){
                max_value = sequence[i];
                now_value = sequence[i];
                continue;
            }

            long weight;
            if(i % 2 == 0){
                weight = 1;
            }else{
                weight = -1;
            }

            long nxt_number = sequence[i] * weight;

            if(nxt_number > now_value + nxt_number){
                now_value = nxt_number;

                max_value = Math.max(max_value, now_value);
            }else{
                now_value = now_value + nxt_number;

                max_value = Math.max(max_value, now_value);
            }

        }

        // -1 1 -1 ...
        for (int i = 0; i < sequence.length; i++){

            long weight;
            if(i % 2 == 0){
                weight = -1;
            }else{
                weight = 1;
            }

            long nxt_number = sequence[i] * weight;

            if(i == 0){
                now_value = nxt_number;

                max_value = Math.max(max_value, now_value);
                continue;
            }

            if(nxt_number > now_value + nxt_number){
                now_value = nxt_number;

                max_value = Math.max(max_value, now_value);
            }else{
                now_value = now_value + nxt_number;

                max_value = Math.max(max_value, now_value);
            }
        }

        return max_value;
    }
}