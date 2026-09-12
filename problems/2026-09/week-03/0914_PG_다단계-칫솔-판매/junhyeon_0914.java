import java.util.*;

class Solution {

    static class Node{

        int number;
        String name;

        int parent;
        int amount;

        // 기본 생성자
        Node(){
            this.number = -1;
            this.name = "";

            this.parent = -1;
            this.amount = -1;
        }

        Node(int number, String name, int parent){
            this.number = number;
            this.name = name;

            this.parent = parent;
            this.amount = 0;
        }
    }

    public int[] solution(String[] enroll, String[] referral, String[] seller, int[] amount) {

        Node[] nodeList = new Node[10001];
        Map<String, Integer> m = new HashMap<>();

        nodeList[0] = new Node(0, "center", -1);

        // node 초기화
        for(int i = 0; i < enroll.length; i++){
            nodeList[i+1] = new Node(i+1, enroll[i], 0);
            m.put(enroll[i], i+1);
        }

        // node의 부모 초기화
        for(int i = 0; i < referral.length; i++){

            if(referral[i].equals("-")){
                continue;
            }

            int parent = m.get(referral[i]);
            nodeList[i+1].parent = parent;

        }

        // 판매 시작
        for(int i = 0; i < seller.length; i++){

            Node nowNode = nodeList[m.get(seller[i])];
            int nowAmount = amount[i] * 100;
            //System.out.println("seller : " + seller[i]);

            while(true){

                if(nowAmount / 10 == 0 || nowNode.number == 0){
                    //System.out.print("name : " + nowNode.name + ", 추가된 금액: ");
                    //System.out.println(nowAmount);

                    nowNode.amount += nowAmount;
                    break;
                }

                int nxtAmount = nowAmount/10;
                nowNode.amount += (nowAmount - nxtAmount);
                //System.out.print("name : " + nowNode.name + ", 추가된 금액: ");
                //System.out.println(nowAmount-nxtAmount);


                nowAmount = nxtAmount;

                nowNode = nodeList[nowNode.parent];
            }
        }

        int[] answer = new int[enroll.length];
        for(int i = 0; i < answer.length; i++){
            answer[i] = nodeList[i+1].amount;
        }

        return answer;
    }
}