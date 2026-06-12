# WORKLOG - ConsoleMVC

> **작성 규칙**
> - Agent는 커밋 후 아래 템플릿으로 작업 내용을 기록하고 WORKLOG를 커밋한다.
> - 리뷰 요청 섹션을 작성 후 사용자에게 리뷰를 요청한다.
> - 사용자는 리뷰 섹션에 피드백/요청사항을 작성 후 커밋한다.
> - Agent는 다음 작업 시작 전 반드시 최신 WORKLOG를 확인한다.

---

## 템플릿

```
## [YYYY-MM-DD] {작업 제목}

### 작업 내용
- 

### 커밋
- `{hash}` {커밋 메시지}

### 리뷰 요청
- 

---
### 리뷰 (by User)
- 

### 다음 작업 지시
- 
```

---

<!-- 실제 로그는 아래에 최신순으로 작성 -->

## [2026-06-12] 콘솔 한글 인코딩 깨짐 수정

### 작업 내용
- 원인: Windows 콘솔 기본 코드페이지(949, EUC-KR)로 인해 UTF-8 문자열이 깨짐
- 수정: `main()` 시작 시 `SetConsoleOutputCP(CP_UTF8)` / `SetConsoleCP(CP_UTF8)` 호출 추가
- 확인: 메인 메뉴 한글 정상 출력 확인

### 커밋
- `ae6fa5b` [AI-Fix] 콘솔 한글 인코딩 깨짐 수정

### 리뷰 요청
- 콘솔에서 한글 정상 출력 확인 부탁드립니다.
- 확인 후 Feature 비즈니스 로직 구현으로 진행하겠습니다.

---
### 리뷰 (by User)
- 정상 출력 확인

### 다음 작업 지시
- 비즈니스 로직 구현

---

## [2026-06-12] 빌드 오류 수정 - /utf-8 옵션 추가

### 작업 내용
- 원인: 한국어 문자열이 포함된 소스 파일을 MSVC가 코드페이지 949(EUC-KR)로 읽어 C2001 오류 발생
- 수정: `ConsoleMVC.vcxproj`, `ConsoleMVCTest.vcxproj` 전 구성(Debug/Release × Win32/x64)에 `/utf-8` 컴파일러 옵션 추가
- 결과: 빌드 성공, **27/27 테스트 통과**

### 커밋
- `b9fcdd4` [AI-Fix] MSVC 빌드 오류 수정 - /utf-8 컴파일러 옵션 추가

### 리뷰 요청
- 빌드 및 테스트 정상 동작 확인 부탁드립니다.
- 확인 후 각 Feature 비즈니스 로직 구현으로 진행하겠습니다.

---
### 리뷰 (by User)
- 정상 빌드됨 확인
- 실행시 콘솔창 한글 인코딩 깨짐

### 다음 작업 지시
- 실행시 콘솔창 한글 인코딩 깨짐 문제 해결

---

## [2026-06-12] MVC 스켈레톤 구조 및 테스트 코드 작성

### 작업 내용
- Model / View(인터페이스 + 구현) / Controller 3계층 패키지 분리 완성
- `model/`: Sample, Order, OrderStatus, SampleRepository, OrderRepository
- `view/`: IXxxView 인터페이스 7개 + 구현 클래스 7개
- `controller/`: IController, MainMenuController + 6개 서브컨트롤러
- `main.cpp`: 전체 의존성 배선(wiring) 완성
- `ConsoleMVCTest/` 프로젝트: 각 Feature별 테스트 코드 작성 (7개 파일)
  - 네비게이션 흐름 테스트 (현재 통과 가능)
  - Feature 비즈니스 로직 테스트 (TODO로 주석 처리 - Feature 구현 후 활성화 예정)
- `ConsoleMVC.slnx`: 테스트 프로젝트 추가
- `ConsoleMVC.vcxproj`: 신규 소스파일 전체 등록

### 커밋
- `50b933f` [AI-Feature] MVC 스켈레톤 구조 구현 및 테스트 코드 작성

### 리뷰 요청
- MVC 계층 분리 구조가 의도에 맞는지 확인 부탁드립니다.
- 테스트 케이스 설계 방향 검토 부탁드립니다.
  - 현재: 네비게이션/뷰 호출 테스트는 즉시 통과 가능, 비즈니스 로직 테스트는 주석 처리
  - Feature 구현 후 주석 해제하여 활성화하는 방식
- 승인 후 각 Feature 비즈니스 로직 구현 단계로 진행하겠습니다.

---
### 리뷰 (by User)
- 계층 분리 잘 진행 된 것 확인
- 추가된 테스트 프로젝트 빌드 불가 (빌드 오류 발생)

### 다음 작업 지시
- MSVC 이용하여 솔루션 직접 빌드하며 빌드 안되는 원인 파악 및 수정

---

## [2026-06-12] PRD.md 및 FEATURES 문서 작성

### 작업 내용
- `Document/PRD.md` 작성: 사용자 관점 기능 요구사항 정리 (메인 메뉴 + 6개 하위 기능)
- `Document/PRD.md` 작성: 사용자 관점 기능 요구사항 (메인 메뉴 + 6개 하위 기능)
- `Document/FEATURES/FEATURE-01-main-menu.md` 작성
- `Document/FEATURES/FEATURE-02-sample-management.md` 작성
- `Document/FEATURES/FEATURE-03-order-placement.md` 작성
- `Document/FEATURES/FEATURE-04-order-approval.md` 작성
- `Document/FEATURES/FEATURE-05-monitoring.md` 작성
- `Document/FEATURES/FEATURE-06-production-line.md` 작성
- `Document/FEATURES/FEATURE-07-release.md` 작성

### 커밋
- (커밋 예정)

### 리뷰 요청
- PRD.md 및 FEATURES 문서 전체 검토 후 승인 부탁드립니다.
- 승인 후 커밋하고 코드 작업을 시작하겠습니다.

---
### 리뷰 (by User)
- PRD.md 파일 확인함.
- 각 Feature .md 파일들 확인했음. 
- 수정 의견 없음

### 다음 작업 지시
- 각 Feature에 대한 Test 코드 개발 후 커밋
- 각 Feature 기능 개발 전 User 검토 요청
