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

## 작업 시작 전 필수 문서 작성

코드 작업 시작 전 아래 두 가지 문서를 반드시 먼저 작성한다.

### 1. Document/PRD.md (Product Requirements Document)
- **사용자 관점**에서 필요한 기능과 요구사항을 기술
- 기술적인 구현 방법, 클래스명, 라이브러리 등 기술 내용은 다루지 않는다
- "사용자는 ~할 수 있어야 한다" 형식으로 작성
- 커밋: `[AI-Docs] Add PRD.md`

### 2. Document/FEATURES/ (기능별 상세 요구사항)
- 각 기능마다 별도의 `.md` 파일로 작성
- 파일명 예시: `FEATURE-01-sample-management.md`, `FEATURE-02-order.md`
- 내용: 기능 목적, 사용자 시나리오, 입력/출력, 예외 처리 기준
- 기술 구현 내용 제외, 요구사항 수준으로 기술
- 커밋: `[AI-Docs] Add FEATURES documents`

### 문서 작성 순서
```
PRD.md 작성 → FEATURES/ 각 파일 작성 → 커밋 → 사용자 리뷰 요청 → 승인 후 코드 작업 시작
```

---

## 개발 환경 및 테스트 정책

### 개발 언어
- **C++** (C++17 이상 권장)
- 빌드 시스템: CMake 사용 권장

### 테스트 프레임워크
- **Google Mock (gmock) / Google Test (gtest)**
- CMakeLists.txt에 테스트 타겟을 별도 구성
- 테스트 파일 위치: `test/` 디렉토리

### 테스트 정책
- TDD(Test-Driven Development)는 강제하지 않는다.
- 단, 구현한 **각 기능에 대해 반드시 테스트 코드를 작성**한다.
- 기능 구현 커밋(`[AI-Feature]`) 이후 테스트 커밋(`[AI-Test]`)을 함께 남긴다.
- 최소 기준: 정상 동작 케이스 + 경계값/예외 케이스 각 1개 이상

---

## 개발 워크플로우 (WORKLOG 기반)

모든 작업은 아래 사이클을 반드시 따른다.
WORKLOG 파일 위치: `Document/WORKLOG.md`

```
1. 작업 시작 전     → Document/WORKLOG.md 열어 최신 내용 확인
                      사용자가 수정한 내용(리뷰/지시)이 있으면 즉시 [USER-Review] 헤더로 커밋 후 진행
2. 작업 및 커밋     → 기능 단위로 [AI-xxx] 헤더로 커밋
3. WORKLOG 업데이트 → 작업 내용 요약, 커밋 해시, 리뷰 요청사항 기록 (커밋 안 함)
4. 사용자 리뷰      → 사용자가 WORKLOG에 피드백/다음 지시 작성
5. 다음 작업        → [USER-Review] 내용 기반으로 1번부터 반복
```

> **규칙**: 작업 시작 시 WORKLOG에 사용자 수정사항이 있으면, 반드시 먼저 `[USER-Review]` 헤더로 커밋한 뒤 작업을 시작한다.

### 커밋 메시지 컨벤션

| 헤더 | 사용 주체 | 사용 시점 |
|------|-----------|-----------|
| `[AI-Feature]` | Agent | 새 기능 구현 |
| `[AI-Fix]` | Agent | 버그 수정 (리뷰 피드백 반영 포함) |
| `[AI-Test]` | Agent | 테스트 코드 작성/수정 |
| `[AI-Refactoring]` | Agent | 리팩토링 (기능 변경 없음) |
| `[AI-Docs]` | Agent | 문서 작성/수정 (PRD, README 등) |
| `[AI-Chore]` | Agent | 빌드 설정, 의존성 추가, 프로젝트 초기 구성 |
| `[USER-Review]` | Agent | 사용자가 WORKLOG 업데이트 후 커밋 요청 시 |

예시:
```
[AI-Feature] 시료 등록 및 조회 기능 구현
[AI-Fix] 중복 ID 허용되던 버그 수정
[AI-Test] 시료 등록 중복 ID 검증 테스트 추가
[AI-Refactoring] SampleController 메서드 분리
[AI-Docs] PRD.md 작성
[AI-Chore] Gradle 프로젝트 초기 구성
[USER-Review] 사용자 리뷰 반영 - 시료 검색 기능 수정 요청
```

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
