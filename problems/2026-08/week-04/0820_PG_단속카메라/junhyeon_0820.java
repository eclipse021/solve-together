import java.util.*;

class Solution {

    static class Car{
        int start;
        int end;

        Car(int start, int end){
            this.start = start;
            this.end = end;
        }
    }

    public int solution(int[][] routes) {

        List<Car> list = new ArrayList<>();

        for(int i = 0; i < routes.length; i++){
            Car c = new Car(routes[i][0], routes[i][1]);
            list.add(c);
        }

        list.sort(
                (a,b) -> {
                    return Integer.compare(a.start, b.start);
                }
        );


        int cnt = 0;
        int cover = 0;

        for(int i = 0; i < list.size(); i++){

            // 맨 처음 원소는 무조건 cnt, cover 세팅
            if(i == 0){
                cnt = 1;
                cover = list.get(i).end;

                continue;
            }

            if(cover > list.get(i).end){
                cover = list.get(i).end;
            }else{

                if(list.get(i).start <= cover){
                    continue;
                }else{
                    cnt++;
                    cover = list.get(i).end;
                }

            }

        }

        return cnt;
    }
}