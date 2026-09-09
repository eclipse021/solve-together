import java.util.*;

class Solution {
    public String solution(int[] numbers) {

        List<Integer> list = new ArrayList<>();

        for(int number : numbers){
            list.add(number);
        }

        list.sort((a,b) -> {

            int first;
            if(b >= 1000){
                first = a * 10000 + b;
            }else if(b >= 100){
                first = a * 1000 + b;
            }else if(b >= 10){
                first = a * 100 + b;
            }else{
                first = a * 10 + b;
            }

            int second;
            if(a>=1000){
                second = b * 10000 + a;
            }else if(a >= 100){
                second = b * 1000 + a;
            }else if(a >= 10){
                second = b * 100 + a;
            }else{
                second = b * 10 + a;
            }

            return Integer.compare(second, first);
        });

        String answer = "";
        for(int num : list){

            if(answer.equals("") && num == 0){
                continue;
            }
            answer += num;
        }

        if(answer.equals("")){
            return "0";
        }
        return answer;
    }
}