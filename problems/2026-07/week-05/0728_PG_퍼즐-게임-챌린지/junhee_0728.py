def solution(diffs, times, limit):
    def solve_puzzle(level):
        time, is_solve = 0, True

        for i in range(len(diffs)):
            if diffs[i] > level:
                resolve_count = diffs[i] - level
                time += (times[i-1] + times[i]) * resolve_count

            time += times[i]

            if time > limit:
                is_solve = False
                break

        return is_solve
    
    start, end = 1, max(diffs)

    while start <= end:
        mid = (start + end) // 2

        if solve_puzzle(mid):
            if mid == 1 or not solve_puzzle(mid-1):
                return mid
            else:
                end = mid - 1
        else:
            start = mid + 1