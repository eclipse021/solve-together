def solution(numbers):
    # 1. 모든 숫자를 문자열로 변환합니다.
    numbers = list(map(str, numbers))
    
    # 2. 문자열을 3번(1000이하라서) 반복한 값(x*3)을 기준으로 내림차순 정렬합니다.
    numbers.sort(key=lambda x: x*3, reverse=True)
    
    # 3. 정렬된 숫자들을 이어 붙여서 하나의 문자열로 만듭니다.
    answer = ''.join(numbers)
    
    # 4. 모든 숫자가 0인 경우('000' 등)를 처리합니다.
    # 정렬을 마쳤는데 가장 큰 첫 번째 숫자가 '0'이라면, 나머지도 모두 '0'이라는 뜻입니다.
    if answer[0] == '0':
        return '0'
        
    return answer