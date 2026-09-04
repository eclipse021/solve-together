def solution(n, wires):
    answer = 99999

    for i in range(len(wires)):
        temp_wires = wires[:i] + wires[i+1:]
        s = {1}
        for j in range(n):
            for wire in temp_wires:
                is_in = False
                for w in wire:
                    if w in s:
                        is_in = True
                        break
                if is_in:
                    s.update(wire)
        temp_answer = abs(n - (len(s) * 2))
        answer = min(answer, temp_answer)

    return answer