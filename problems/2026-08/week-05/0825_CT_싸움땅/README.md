# 싸움땅

- 문제: [코드트리 문제 바로가기](https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/battle-ground/description)
- 날짜: 2026-08-25
- 플랫폼: CT
- 제한 시간: 40분

## 풀이 기록

| 이름 | 결과 |   풀이 시간 | 힌트/풀이 참고 |
| --- |----|--------:|:--------:|
| 준현 | 성공 | 1시간 30분 |    X     |
| 준희 | -  |       - |    -     |

결과는 `성공`, `미완료`, `재풀이 필요` 중 하나로 기록합니다.

## 짧은 회고

### 준현

- 접근: winner, loser을 레퍼런스로 할당 후 winner, loser 를 조작해서 시뮬레이션 작성
- 막힌 지점: winner/loser 를 human&로 먼저 선언한 뒤 다른 객체를 대입해 참조 대상을 바꾸려고 했는데, 레퍼런스는 선언할 때 바인딩된 대상을 이후 변경할 수 없었다.
- 다음에 기억할 것:
  1. 레퍼런스를 쓸 때는 먼저 winner_index, loser_index를 결정한 뒤 human& winner = humans[winner_index]처럼 마지막에 바인딩하자.
  2. 조건에 따라 가리킬 대상을 인덱스 없이 가리켜야 한다면 포인터를 사용하자 -> human* winner = &humans[i]처럼 저장하고 멤버 접근은 winner->weapon으로 한다.
  3. 포인터가 가리키는 객체를 레퍼런스 인자로 넘길 때는 func(*winner)처럼 *로 값을 가져와 넘기기!(주의)

### 준희

- 접근:
- 막힌 지점:
- 다음에 기억할 것:
