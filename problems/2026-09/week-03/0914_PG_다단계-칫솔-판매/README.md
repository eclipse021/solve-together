# 다단계 칫솔 판매

- 문제: [프로그래머스 문제 바로가기](https://school.programmers.co.kr/learn/courses/30/lessons/77486)
- 날짜: 2026-09-14
- 플랫폼: PG
- 제한 시간: 40분

## 풀이 기록

| 이름 | 결과 | 풀이 시간 | 힌트/풀이 참고 |
| --- |----|------:|:--------:|
| 준현 | 성공 |   40분 |    x     |
| 준희 | -  |     - |    -     |

결과는 `성공`, `미완료`, `재풀이 필요` 중 하나로 기록합니다.

## 짧은 회고

### 준현

- 접근: 각 사람 정보는 ArrayList, 사람-번호는 HashMap으로 저장 후 시뮬레이션으로 해결
- 막힌 지점: 오랜만에 자바 적용해서 그런지 Map 관련 문법 헷갈림
- 다음에 기억할 것:
  - 자바 문법
    - 원소 대입 : m.put(a,b) / 원소 가져오기 : m.get(a) / 원소 key/value 있는지 검사 : m.containsKey(a) or m.containsValue(b) / 원소 제거 : m.remove(a)
    - map 순회 :
        ```
        for(var v : m.entrySet()){
            var a = v.getKey();
            var b = b.getValue();
        }
      ```
### 준희

- 접근:
- 막힌 지점:
- 다음에 기억할 것:
