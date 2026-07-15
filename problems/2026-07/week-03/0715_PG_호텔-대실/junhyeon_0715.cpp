//
// Created by 임준현 on 26. 7. 15.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 00:00 부터 23:59 까지 1분당 한 공간 차지
int time_record[1500];

int parse(string s) {

    int n0 = s[0] - '0';
    int n1 = s[1] - '0';

    int n3 = s[3] - '0';
    int n4 = s[4] - '0';


    int hour = n0 * 10 + n1 ;
    int minute = n3 * 10 + n4 ;

    cout << "------------- \n";
    cout << hour << ":" << minute << "\n";
    cout << "------------- \n";


    return hour * 60 + minute;
}

void record(vector<string> s) {

    int start = parse(s[0]);
    int end = parse(s[1]);

    for (int i = start; i < end + 10; i++) {
        time_record[i] += 1;
    }
}

int solution(vector<vector<string>> book_time) {

    // 초기화
    for (int i = 0; i < 1500; i++) {
        time_record[i] = 0;
    }

    for (vector<string> book : book_time) {
        record(book);
    }

    int answer = 0;

    for (int i = 0; i < 1500; i++) {
        answer = max(answer, time_record[i]);
    }

    return answer;
}