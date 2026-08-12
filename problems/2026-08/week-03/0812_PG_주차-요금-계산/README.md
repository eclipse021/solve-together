# 주차 요금 계산

- 문제: [프로그래머스 문제 바로가기](https://school.programmers.co.kr/learn/courses/30/lessons/92341)
- 날짜: 2026-08-12
- 플랫폼: PG
- 제한 시간: 40분

## 풀이 기록

| 이름 | 결과 | 풀이 시간 | 힌트/풀이 참고 |
| --- | --- | ---: | :---: |
| 준현 | 성공 | - | 자바 문법 참고 |
| 준희 | - | - | - |

결과는 `성공`, `미완료`, `재풀이 필요` 중 하나로 기록합니다.

## 짧은 회고

### 준현

- 접근: 기존 C++ 풀이 감각을 유지하면서 `HashMap`, `ArrayList`, 사용자 정의 클래스, 람다 정렬 등을 Java 문법으로 옮겨 구현함.
- 막힌 지점: `string`/`String`, 컬렉션 `import`, 생성자, 배열과 `List` 접근 방식 차이 등 Java 문법 차이에서 컴파일 에러가 다수 발생함.
- 다음에 기억할 것:
  - 문자열: `str.charAt(i)`, `str.substring(start, end)`, `Integer.parseInt(str)`를 사용하고, 한 자리 숫자는 `str.charAt(i) - '0'`으로 변환한다.
  - `Map`: `put()`은 추가와 수정에 모두 사용하며, `getOrDefault()`, `containsKey()`를 활용한다. 순회는 `for (var e : map.entrySet())`로 할 수 있다.
  - `List`: `add()`, `get(i)`, `set(i, value)`를 사용하며, 정렬은 `list.sort((a, b) -> Integer.compare(...))`로 구현한다.
  - 배열: `arr[i]`로 접근하고 `.set()`은 사용할 수 없다.
  - 사용자 정의 클래스에서 `new Info(a, b)`를 사용하려면 생성자를 직접 정의해야 한다.
  - `String`, `Map`, `List` 등의 대소문자에 주의하고 `import java.util.*;`를 빼먹지 말자.

### 준희

- 접근:
- 막힌 지점:
- 다음에 기억할 것:
