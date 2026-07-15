import heapq


def time2min(time):
    h, m = int(time[0:2]), int(time[3:])
    return h * 60 + m

def solution(book_time):
    book_time.sort()
    q = []

    for start, end in book_time:
        s_min, e_min = time2min(start), time2min(end) + 10

        if q and q[0] <= s_min:
            heapq.heappop(q)
            
        heapq.heappush(q, e_min)

    return len(q)