import java.util.*;

class Solution {

    static int time2int(String str) {
        int h1 = str.charAt(0) - '0';
        int h2 = str.charAt(1) - '0';

        int m1 = str.charAt(3) - '0';
        int m2 = str.charAt(4) - '0';

        return (h1 * 10 + h2) * 60 + (m1 * 10 + m2);
    }

    static class Info {
        int number;
        int fee;

        Info(int number, int fee) {
            this.number = number;
            this.fee = fee;
        }
    }

    static int calculate_fee(
            int total_time,
            int standard_time,
            int standard_fee,
            int plus_time,
            int plus_fee) {

        if (total_time <= standard_time) {
            return standard_fee;
        }

        int temp = total_time - standard_time;

        if (temp % plus_time == 0) {
            temp = temp / plus_time;
        } else {
            temp = temp / plus_time;
            temp++;
        }

        return standard_fee + temp * plus_fee;
    }

    public int[] solution(int[] fees, String[] records) {

        Map<Integer, Integer> in_m = new HashMap<>();
        Map<Integer, Integer> out_m = new HashMap<>();
        Map<Integer, Integer> total_m = new HashMap<>();

        for (String str : records) {

            String time_str = str.substring(0, 5);
            String number_str = str.substring(6, 10);
            String status_str = str.substring(11, 13);

            int time = time2int(time_str);
            int number = Integer.parseInt(number_str);

            if (status_str.equals("IN")) {

                // 가장 최근 입차 시간
                in_m.put(number, time);

            } else {

                // 가장 최근 출차 시간
                out_m.put(number, time);

                // 이번 주차 시간
                int in_time = in_m.get(number);
                int parking_time = time - in_time;

                // 누적
                total_m.put(number, total_m.getOrDefault(number, 0) + parking_time);
            }
        }

        // 마지막 OUT이 없는 차량 처리
        int end_time = time2int("23:59");

        for (var entry : in_m.entrySet()) {

            int number = entry.getKey();
            int in_time = entry.getValue();

            if (!out_m.containsKey(number)|| in_time > out_m.get(number)) {

                int parking_time = end_time - in_time;

                total_m.put(number, total_m.getOrDefault(number, 0) + parking_time);
            }
        }

        List<Info> info_list = new ArrayList<>();

        int standard_time = fees[0];
        int standard_fee = fees[1];
        int plus_time = fees[2];
        int plus_fee = fees[3];

        for (var entry : total_m.entrySet()) {

            int number = entry.getKey();
            int total_time = entry.getValue();

            int fee = calculate_fee(
                    total_time,
                    standard_time,
                    standard_fee,
                    plus_time,
                    plus_fee
            );

            info_list.add(new Info(number, fee));
        }

        info_list.sort((a, b) ->{
            return Integer.compare(a.number, b.number);
        });

        int[] answer = new int[info_list.size()];

        for (int i = 0; i < info_list.size(); i++) {
            answer[i] = info_list.get(i).fee;
        }

        return answer;
    }
}