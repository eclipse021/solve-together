import java.util.*;

class Solution {

    static List<Integer>[][][][] info_list = new ArrayList[3][2][2][2];
    static List<Integer> result = new ArrayList<>();

    static int searchBinary(int start, int end, int target, List<Integer> list){

        if(start > end){
            return 0;
        }

        int mid = (start+end) / 2;

        if(list.get(mid) < target){
            return searchBinary(mid + 1, end, target, list);
        }else {

            if(mid == 0){
                return list.size();
            }

            if(list.get(mid - 1) < target){
                return list.size() - mid;
            }

            return searchBinary(start, mid-1, target, list);
        }

    }

    public int[] solution(String[] info, String[] query) {

        // info_list 초기화
        for(int a = 0; a < 3; a++){
            for(int b = 0; b < 2; b++){
                for(int c = 0; c < 2; c++){
                    for(int d = 0; d<2 ; d++){
                        info_list[a][b][c][d] = new ArrayList<>();
                    }
                }
            }
        }

        // info_list 세팅
        for(String str: info){

            String[] s = str.split(" ");
            int a,b,c,d;

            // a 세팅
            if(s[0].equals("cpp")){
                a = 0;
            }else if(s[0].equals("java")){
                a = 1;
            }else{
                a = 2;
            }

            // b 세팅
            if(s[1].equals("backend")){
                b = 0;
            }else{
                b = 1;
            }

            // c 세팅
            if(s[2].equals("junior")){
                c = 0;
            }else{
                c = 1;
            }

            // d 세팅
            if(s[3].equals("chicken")){
                d = 0;
            }else{
                d = 1;
            }

            info_list[a][b][c][d].add(Integer.parseInt(s[4]));
        }

        // info_list 오름차순 정렬
        for(int a = 0; a < 3; a++){
            for(int b = 0; b < 2; b++){
                for(int c = 0; c < 2; c++){
                    for(int d = 0; d<2 ; d++){
                        info_list[a][b][c][d].sort((x,y)->{
                            return Integer.compare(x,y);
                        });
                    }
                }
            }
        }

        // 각 query에 대한 만족하는 사람 수 찾기
        for(String str : query){

            String[] s = str.split(" ");

            List<Integer> list1 = new ArrayList<>();
            List<Integer> list2 = new ArrayList<>();
            List<Integer> list3 = new ArrayList<>();
            List<Integer> list4 = new ArrayList<>();

            if(s[0].equals("cpp")){
                list1.add(0);
            }else if(s[0].equals("java")){
                list1.add(1);
            }else if(s[0].equals("python")){
                list1.add(2);
            }else{
                list1.add(0); list1.add(1); list1.add(2);
            }

            if(s[2].equals("backend")){
                list2.add(0);
            }else if(s[2].equals("frontend")){
                list2.add(1);
            }else{
                list2.add(0); list2.add(1);
            }

            if(s[4].equals("junior")){
                list3.add(0);
            }else if(s[4].equals("senior")){
                list3.add(1);
            }else{
                list3.add(0); list3.add(1);
            }

            if(s[6].equals("chicken")){
                list4.add(0);
            }else if(s[6].equals("pizza")){
                list4.add(1);
            }else{
                list4.add(0); list4.add(1);
            }

            int total = 0;
            int target = Integer.parseInt(s[7]);

            for(int a : list1){
                for(int b : list2){
                    for(int c : list3){
                        for(int d : list4){

                            total += searchBinary(0, info_list[a][b][c][d].size()-1, target, info_list[a][b][c][d] );
                        }
                    }
                }
            }

            result.add(total);

        }

        int[] answer = new int[result.size()];
        for(int i = 0; i < result.size(); i++){
            answer[i] = result.get(i);
        }

        return answer;
    }
}