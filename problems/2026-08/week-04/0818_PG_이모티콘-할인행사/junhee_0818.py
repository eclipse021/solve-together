from itertools import product


def solution(users, emoticons):
    max_plus, max_money = 0, 0
    for p in product([10, 20, 30, 40], repeat=len(emoticons)):
        temp_plus, temp_money = 0, 0
        for i in range(len(users)):
            user_cost = 0
            for j in range(len(emoticons)):
                # 사는 경우
                if users[i][0] <= p[j]:
                    user_cost += emoticons[j] * (100 - p[j]) // 100

            if user_cost >= users[i][1]:
                temp_plus += 1
            else:
                temp_money += user_cost

        if temp_plus > max_plus:
            max_plus = temp_plus
            max_money = temp_money
        elif temp_plus == max_plus and temp_money > max_money:
            max_money = temp_money
        
    return [max_plus, max_money]