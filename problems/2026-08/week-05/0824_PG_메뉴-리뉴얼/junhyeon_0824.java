import java.util.*;

class Solution {

    // map 선언 부분 오류
    static Map<Integer, Integer> um = new HashMap<>();
    static int[] weight = new int[26];

    static class Node{
        String str;
        int cnt;

        Node(String str, int cnt){
            this.str = str;
            this.cnt = cnt;
        }
    }

    static Node intToNode(int num){

        String str = "";
        char c = 'A';
        int cnt = 0;

        // char -> String ?? String -> char 공부하기
        for(int i = 0; i < 26; i++){

            if(num % 2 == 1){
                str += c;
                cnt++;
            }
            num /= 2;
            c += 1;
        }

        Node node = new Node(str, cnt);
        return node;
    }

    // String은 깊은 복사, 얕은 복사?
    static void dfs(int nowIndex, int nowCnt, int target, int nowOrder ,String order){

        if(nowCnt == target){

            // containsKey, containsValue
            if(um.containsKey(nowOrder)){
                int num = um.get(nowOrder);

                um.put(nowOrder, num + 1);
            }else{
                um.put(nowOrder, 1);
            }

            return;
        }

        for(int i = nowIndex + 1; i < order.length(); i++){
            int value = weight[order.charAt(i) - 'A'];

            dfs(i, nowCnt + 1, target, nowOrder + value, order);
        }

    }

    public String[] solution(String[] orders, int[] course) {

        int index = 1;
        for(int i = 0; i < 26; i++){
            weight[i] = index;
            index *= 2;
        }

        for(String order : orders){
            for(int i = 2; i <= order.length(); i++ ){
                dfs(-1, 0, i, 0, order);
            }
        }

        int[] most = new int[11];
        for(int i = 0; i < 11; i++){
            most[i] = 0;
        }

        for(var element : um.entrySet()){
            int value = element.getValue();
            Node node = intToNode(element.getKey());
            String key = node.str;
            int cnt = node.cnt;

            most[cnt] = Math.max(most[cnt], value);
        }



        List<String> answer = new ArrayList<>();

        // map 순회
        for(var element : um.entrySet()){

            int value = element.getValue();
            Node node = intToNode(element.getKey());
            String key = node.str;
            int cnt = node.cnt;

            if(value == 1){
                continue;
            }

            if(value != most[cnt]){
                continue;
            }

            for(int c : course){
                if(c == cnt){

                    answer.add(key);
                    break;
                }

            }
        }

        // 문자열 정렬
        answer.sort((a,b)->{
            return a.compareTo(b);
        });


        // array -> List, List -> array
        String[] result = new String[answer.size()];
        for(int i = 0; i < answer.size(); i++){
            result[i] = answer.get(i);
        }

        return result;


        // array -> List, List -> array
        //return answer.toArray(new String[0]);

    }
}