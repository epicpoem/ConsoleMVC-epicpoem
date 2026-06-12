# ConsoleMVC - MVC 스켈레톤 PoC Agent

## 역할
반도체 시료 생산주문관리 시스템의 **콘솔 기반 MVC 구조**를 검증하는 PoC.
실제 비즈니스 로직보다 **패키지 구조와 계층 분리**가 목적이다.

## 상위 Orchestrator
`../CLAUDE.md` 참조. 스펙 문서: `../Document/spec/spec_reference.txt`

---

## 구현 목표

Model / Controller / View 3계층을 패키지로 분리하고,
콘솔 입출력 흐름이 올바른 계층을 통해 처리되는 구조를 완성한다.

### 계층별 역할
| 계층 | 역할 | 예시 |
|------|------|------|
| Model | 데이터 구조 및 비즈니스 규칙 | Sample, Order, ProductionLine |
| Controller | 입력 처리 및 흐름 제어 | SampleController, OrderController |
| View | 콘솔 출력 전담 | MainMenuView, SampleView |

### 구현할 메뉴 구조 (스켈레톤 수준)
```
[메인 메뉴]
  [1] 시료 관리    → SampleController → SampleView
  [2] 시료 주문    → OrderController  → OrderView
  [3] 주문 승인/거절
  [4] 모니터링
  [5] 생산라인 조회
  [6] 출고 처리
  [0] 종료
```

---

## 구현 범위 제한

- 각 메뉴 진입 및 반환 흐름만 동작하면 충분
- 실제 데이터 처리 로직은 Stub/Placeholder 수준으로 구현
- 데이터 영속성 불필요 (메모리 내 처리만)

---

## 제출 기준

- [ ] Model / Controller / View 패키지가 명확히 분리됨
- [ ] 메인 메뉴에서 각 하위 메뉴 진입/복귀 동작
- [ ] 각 계층이 직접 다른 계층을 우회하지 않음 (단방향 의존)
- [ ] CLAUDE.md 존재
- [ ] 의미있는 커밋 이력

---

## 공통 제약
- 모델: **Sonnet / Effort: Medium** 만 허용 (Opus 사용 금지)
- Repository: Public 유지
