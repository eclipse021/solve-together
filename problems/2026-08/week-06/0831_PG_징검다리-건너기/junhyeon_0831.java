class Solution {

    static int find_max(int [] stones, int mid){

        int[] temp = stones.clone();

        for(int i = 0; i < temp.length; i++){
            temp[i] -= mid;
        }

        int max_value = 0;
        int cnt = 0;
        for(int i = 0; i < temp.length; i++){

            if(temp[i] > 0){
                cnt = 0;
            }else{
                cnt++;
            }

            max_value = Math.max(max_value, cnt);
        }

        return max_value;

    }

    static int binarySearch(int[] stones, int k, int start, int end){

        if(start > end){
            return -1;
        }

        int mid = (start+end) / 2;

        int max_value = find_max(stones, mid);


        if(max_value < k){
            return binarySearch(stones, k, mid + 1, end);
        }else{

            max_value = find_max(stones, mid - 1);

            if(max_value < k){
                return mid;
            }

            return binarySearch(stones, k , start, mid - 1);
        }

    }

    public int solution(int[] stones, int k) {
        int answer = binarySearch(stones, k, 1, 200000000);
        return answer;
    }
}