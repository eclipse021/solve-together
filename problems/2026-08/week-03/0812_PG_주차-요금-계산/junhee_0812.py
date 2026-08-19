from math import ceil


def info(r):
    time, car_num, act = r.split()
    time = int(time[0:2]) * 60 + int(time[3:5])
    return (time, car_num, act)

def solution(fees, records):
    answer = []
    parking, total_time = dict(), dict()
    max_time = 1439
    
    for record in records:
        time, car_num, act = info(record)
        if act == "IN":
            parking[car_num] = time
        elif act == "OUT":
            parked_time = time - parking[car_num]
            total_time[car_num] = total_time.get(car_num, 0) + parked_time
            del parking[car_num]
    
    if parking:
        for key, value in parking.items():
            parked_time = max_time - value
            total_time[key] = total_time.get(key, 0) + parked_time
            
    for _, time in sorted(total_time.items()):
        if time <= fees[0]:
            answer.append(fees[1])
        else:
            more_time = time - fees[0]
            more_fee = ceil(more_time / fees[2]) * fees[3]
            answer.append(fees[1] + more_fee)
    
    return answer