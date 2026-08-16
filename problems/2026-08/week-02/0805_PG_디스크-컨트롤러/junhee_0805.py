import heapq


def solution(jobs):
    answer = 0
    jobs_amount, now_time, i = len(jobs), 0, 0
    jobs.sort(key=lambda x: x[0])
    q = []

    while i < jobs_amount or q:
        if q:
            job_time, start_time, _ = heapq.heappop(q)
            now_time += job_time
            answer += now_time - start_time
        else:
            now_time = jobs[i][0]

        while i < jobs_amount and jobs[i][0] <= now_time:
            heapq.heappush(q, (jobs[i][1], jobs[i][0], i))
            i += 1

    return answer // jobs_amount