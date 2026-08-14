import java.util.*;

class Solution {

    static long binary_search(long n, long start, long end, List<Long> time_list){

        if(start > end){
            return -1;
        }

        long mid = (start + end) / 2;

        // mid == 1 일 때 생각하기 -> 인덱스가 아니라 시간이니 0분이어도 괜찮을듯

        long total = 0;
        for(Long time : time_list){
            total += mid / time;
        }

        // 성공
        if(total >= n){

            long left_total = 0;
            for (Long time : time_list){
                left_total += (mid-1) / time;
            }

            if (left_total < n){
                return mid;
            }else{
                return binary_search(n, start, mid-1, time_list);
            }

        }else{ // 실패
            return binary_search(n, mid + 1, end, time_list);
        }

    }

    public long solution(int n, int[] times) {

        List<Long> time_list = new ArrayList<>();

        for(int i = 0; i < times.length; i++){
            time_list.add((long) times[i]);
        }

        time_list.sort((a,b) -> {
            return Long.compare(a, b);
        });

        long answer = binary_search(n, 1, 1000000000000000000L, time_list); // start : 최소인 1, end : 최악인 10억 * 10억
        return answer;
    }
}