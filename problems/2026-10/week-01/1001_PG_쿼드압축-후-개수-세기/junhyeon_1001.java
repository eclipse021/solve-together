import java.util.*;

class Solution {

    static int zeroCnt = 0;
    static int oneCnt = 0;

    static void find(int r, int c, int size, int[][] arr){

        boolean isSame = true;
        for(int i = r; i < r + size; i++){
            for(int j = c; j < c + size; j++){

                if(arr[i][j] != arr[r][c]){
                    isSame = false;
                }

            }

        }

        if(isSame){
            if(arr[r][c] == 0){
                zeroCnt++;
            }else if(arr[r][c] == 1){
                oneCnt++;
            }

            return;
        }

        if(size == 1){
            return;
        }

        find(r, c, size/2, arr);
        find(r+size/2, c, size/2, arr);
        find(r, c+size/2, size/2, arr);
        find(r+size/2, c+size/2, size/2, arr);


    }

    public int[] solution(int[][] arr) {

        int size = arr.length;

        find(0, 0, size, arr);

        int[] answer = new int[2];

        answer[0] = zeroCnt;
        answer[1] = oneCnt;

        return answer;
    }
}