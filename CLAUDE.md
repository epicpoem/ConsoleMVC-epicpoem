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

## 개발 워크플로우 (WORKLOG 기반)

모든 작업은 아래 사이클을 반드시 따른다.
WORKLOG 파일 위치: `Document/WORKLOG.md`

```
1. 작업 시작 전  → Document/WORKLOG.md 열어 최신 리뷰/지시사항 확인
2. 작업 및 커밋  → 기능 단위로 커밋
3. WORKLOG 업데이트 → 작업 내용 요약, 커밋 해시, 리뷰 요청사항 기록
4. WORKLOG 커밋  → "docs: update WORKLOG" 메시지로 커밋 및 푸시
5. 사용자 리뷰   → 사용자가 WORKLOG에 피드백/다음 지시 작성 후 커밋
6. 1번으로 반복
```

### 커밋 메시지 컨벤션
모든 커밋 메시지는 아래 헤더 중 하나로 시작한다.

| 헤더 | 사용 시점 |
|------|-----------|
| `[AI-Feature]` | 새 기능 구현 |
| `[AI-Test]` | 테스트 코드 작성/수정 |
| `[AI-Refactoring]` | 리팩토링 (기능 변경 없음) |
| `[AI-Docs]` | 문서 작성/수정 (PRD, README 등) |

예시:
```
[AI-Feature] 시료 등록 및 조회 기능 구현
[AI-Test] 시료 등록 중복 ID 검증 테스트 추가
[AI-Refactoring] SampleController 메서드 분리
```

WORKLOG 커밋은 예외: `docs: update WORKLOG`

### WORKLOG 작성 형식
```markdown
## [YYYY-MM-DD] {작업 제목}

### 작업 내용
- 구현한 내용 요약

### 커밋
- `{hash}` {커밋 메시지}

### 리뷰 요청
- 확인 또는 판단이 필요한 사항

---
### 리뷰 (by User)
- (사용자 작성)

### 다음 작업 지시
- (사용자 작성)
```

---

## 공통 제약
- 모델: **Sonnet / Effort: Medium** 만 허용 (Opus 사용 금지)
- Repository: Public 유지
