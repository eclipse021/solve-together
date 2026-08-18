import java.util.*;

class Solution {

    static class Result{
        int signup;
        int money;

        Result(int signup, int money){
            this.signup = signup;
            this.money = money;
        }
    }

    static List<Result> result_list = new ArrayList<>();

    static void dfs(int cnt, int[] emoticons_rate, int target, int[][] users, int[] emoticons){

        if(cnt == target){

            int total_signup = 0;
            int total_money = 0;

            for(int i = 0; i<users.length; i++){

                int user_rate = users[i][0];
                int user_money = users[i][1];

                int now_money = 0;
                int now_signup = 0;

                for(int j = 0; j < emoticons.length; j++){

                    if(user_rate <= emoticons_rate[j]){
                        now_money += emoticons[j] * (100-emoticons_rate[j]) / 100;
                    }

                }

                if(user_money <= now_money){
                    now_money = 0;
                    now_signup = 1;
                }

                total_money += now_money;
                total_signup += now_signup;

            }

            Result result = new Result(total_signup, total_money);
            result_list.add(result);

            return;
        }

        for(int i = 10; i<=40; i+=10){
            int[] new_emoticons_rate = emoticons_rate.clone();
            new_emoticons_rate[cnt] = i;

            dfs(cnt + 1, new_emoticons_rate, target, users, emoticons);

        }


    }

    public int[] solution(int[][] users, int[] emoticons) {

        int n = users.length;
        int m = emoticons.length;

        int[] emoticons_rate = new int[7];

        dfs(0, emoticons_rate, m, users, emoticons);

        result_list.sort((a,b)->{

            if(a.signup != b.signup){
                return Integer.compare(b.signup, a.signup);
            }
            return Integer.compare(b.money, a.money);

        });

        int[] answer = {result_list.get(0).signup, result_list.get(0).money};
        return answer;
    }
}