//
// Created by 임준현 on 26. 8. 4.
//
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct disk {

    int number;
    int ask_time;
    int duration;

    disk(int number, int ask_time, int duration) {
        this->number = number;
        this->ask_time = ask_time;
        this->duration = duration;
    }

};

bool vc_cmp(disk& a, disk& b) {
    return a.ask_time < b.ask_time;
}

struct pq_cmp {

    bool operator() (disk& a, disk& b) {
        if (a.duration != b.duration) {
            return a.duration > b.duration;
        }

        if (a.ask_time != b.ask_time) {
            return a.ask_time > b.ask_time;
        }

        return a.number > b.number;

    }
};


int solution(vector<vector<int>> jobs) {

    vector<disk> disk_list;
    for (int i = 0; i < jobs.size(); i++) {

        disk d = disk(i, jobs[i][0], jobs[i][1]);
        disk_list.push_back(d);

    }
    sort(disk_list.begin(), disk_list.end(), vc_cmp);

    int now_time = 0;
    int now_index = 0;
    int answer = 0;
    int job_size = jobs.size();
    priority_queue<disk, vector<disk>, pq_cmp> pq;

    while (true) {

        if (now_index == disk_list.size() && pq.empty()) {
            break;
        }

        while (now_index < disk_list.size()) {
            if (disk_list[now_index].ask_time <= now_time) {
                pq.push(disk_list[now_index]);
                now_index++;
            }else {
                break;
            }
        }

        if (pq.empty()) {
            now_time++;
            continue;
        }

        auto cur = pq.top();
        pq.pop();

        now_time += cur.duration;
        answer += now_time - cur.ask_time;
    }

    return answer / job_size;
}