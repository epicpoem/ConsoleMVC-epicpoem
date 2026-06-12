# ConsoleMVC — 반도체 시료 생산주문관리 시스템 PoC

반도체 시료 생산주문관리 시스템(`SampleOrderSystem`)의 **MVC 계층 구조**를 검증하기 위한 PoC(Proof of Concept) 프로젝트입니다.  
실제 비즈니스 로직보다 **패키지 구조와 계층 분리**가 목적이며, 이후 `SampleOrderSystem`에서 이 구조를 그대로 활용합니다.

---

## 프로젝트 개요

| 항목 | 내용 |
|------|------|
| 언어 | C++20 (MSVC v145) |
| 빌드 | Visual Studio 2022 (.slnx) |
| 테스트 | Google Test / Google Mock (NuGet, gmock 1.11.0) |
| 데이터 저장 | 인메모리 (PoC 범위) |
| 설계 패턴 | MVC + Repository 패턴 + 인터페이스 기반 의존성 주입 |

---

## 아키텍처

### 계층 구조

```
┌─────────────────────────────────────────────────┐
│                    main.cpp                     │  의존성 배선(Wiring)
└─────────────┬───────────────────────────────────┘
              │
┌─────────────▼───────────────────────────────────┐
│              Controller Layer                   │
│  MainMenuController                             │
│  SampleController / OrderController             │
│  ApprovalController / MonitoringController      │
│  ProductionLineController / ReleaseController   │
└─────────────┬───────────────────────────────────┘
              │ 인터페이스 참조
┌─────────────▼───────────────────────────────────┐
│                View Layer                       │
│  IXxxView (인터페이스)  ←  XxxView (구현체)      │
└─────────────────────────────────────────────────┘
              │ 인터페이스 참조
┌─────────────▼───────────────────────────────────┐
│               Model Layer                       │
│  ISampleRepository / IOrderRepository (인터페이스)│
│  SampleRepository / OrderRepository (인메모리)   │
│  IClock (인터페이스) ← SystemClock (구현체)      │
└─────────────────────────────────────────────────┘
```

### DataPersistence 연동 설계

컨트롤러는 `ISampleRepository` / `IOrderRepository` **인터페이스**에만 의존합니다.  
`DataPersistence` PoC 완성 후 `main.cpp`에서 구현체만 교체하면 JSON 저장/로드로 전환 가능합니다.

```cpp
// 현재 (인메모리)
SampleRepository sampleRepo;   // ISampleRepository 구현체

// DataPersistence 연동 후
JsonSampleRepository sampleRepo("data/samples.json");  // 교체만 하면 됨
```

---

## 개발 내용

### 메뉴 구조

```
[메인 메뉴]
  [1] 시료 관리      → 시료 등록 / 조회 / 검색
  [2] 시료 주문      → 주문 접수 (RESERVED)
  [3] 주문 승인/거절  → CONFIRMED / PRODUCING / REJECTED
  [4] 모니터링       → 주문 현황 및 재고 상태 조회
  [5] 생산라인 조회   → 현재 생산 진행상황 (PRODUCING→CONFIRMED 자동 전환)
  [6] 출고 처리      → 출고 처리 및 재고 차감
  [0] 종료
```

### 주요 비즈니스 로직

| 기능 | 로직 |
|------|------|
| 시료 등록 | ID 중복 시 재입력 유도, 수율 0~1 범위 검증 |
| 주문 승인 | 물리적 재고 기반 판단 (보유재고 + PRODUCING 진행분 비례 합산) |
| 실생산량 계산 | `ceil(부족분 / (수율 × 0.9))` — 10% 공정오차 보정 포함 |
| 생산 자동 전환 | PRODUCING → CONFIRMED (경과시간 ≥ 전체생산시간 시 자동 전환) |
| Clock 추상화 | `IClock` 인터페이스 — 실제 환경: `SystemClock`, 테스트: `FakeClock` |

### 주문 상태 흐름

```
RESERVED → CONFIRMED  (재고 충분 시 승인)
         → PRODUCING  (재고 부족 시 승인 + 생산 시작)
         → REJECTED   (거절)

PRODUCING → CONFIRMED (생산라인 조회 시 자동 전환)

CONFIRMED → RELEASE   (출고 처리)
```

---

## 빌드 및 실행

### 요구 환경

- Visual Studio 2022 (v18+)
- MSVC v145 (C++20)
- NuGet 패키지: `googletest` 1.11.0 (자동 복원)

### 빌드

```
Visual Studio에서 ConsoleMVC.slnx 열기
→ 빌드 구성: Debug | x64
→ Ctrl+Shift+B (전체 솔루션 빌드)
```

또는 MSBuild CLI:

```powershell
& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" `
  ConsoleMVC\ConsoleMVC.slnx /p:Configuration=Debug /p:Platform=x64 /m
```

### 실행

```
x64\Debug\ConsoleMVC.exe
```

### 테스트 실행

```
x64\Debug\ConsoleMVCTest.exe
```

---

## 실행 결과 예시

### 메인 메뉴

```
[시스템 현황]
  등록 시료    : 2 종
  총 재고      : 150 ea
  전체 주문    : 3 건
  생산라인 대기: 1 건

========================================
   반도체 시료 생산주문관리 시스템
========================================
 [1] 시료 관리
 [2] 시료 주문
 [3] 주문 승인/거절
 [4] 모니터링
 [5] 생산라인 조회
 [6] 출고 처리
 [0] 종료
========================================
선택: 
```

### 시료 등록

```
--- 시료 관리 ---
 [1] 시료 등록
 [2] 시료 조회
 [3] 시료 검색
 [0] 뒤로
선택: 1

[시료 등록]
시료 ID   : S-001
이름      : SiC Wafer
평균생산시간(min/ea): 0.8
수율(0~1) : 0.92
[성공] 시료가 등록되었습니다.
  ID: S-001 | 이름: SiC Wafer | 평균생산시간: 0.8 min/ea | 수율: 0.92
```

### 주문 승인 (재고 부족 → 생산 시작)

```
[주문 승인/거절]
 1. ORD-20260612-0001 | S-001 | Samsung | 200 ea | RESERVED

선택 (0: 뒤로): 1
[Y] 승인 / [N] 거절: Y

[재고 부족] 현재 물리적 재고: 30 ea
  부족분     : 170 ea
  실생산량   : 206 ea  (수율 0.92 × 0.9 보정)
  예상 생산시간: 164.8 분
생산을 진행하시겠습니까? (Y/N): Y

[처리 완료] 주문 상태: PRODUCING
```

### 테스트 결과

```
[==========] Running 54 tests from 7 test suites.
[  PASSED  ] 54 tests.
```

---

## 테스트 구성

| 파일 | 테스트 수 | 주요 검증 |
|------|-----------|-----------|
| MainMenuControllerTest | 10 | 메뉴 네비게이션, 서브컨트롤러 호출, 현황 요약 표시 |
| SampleControllerTest | 10 | 등록/조회/검색 + 수율 범위 Negative TC |
| OrderControllerTest | 6 | 주문 생성 + 음수/비숫자 수량 Negative TC |
| ApprovalControllerTest | 12 | 승인/거절 + 물리적 재고 + 공식 검증 + Negative TC |
| MonitoringControllerTest | 4 | 주문 통계 및 재고 상태 표시 |
| ProductionLineControllerTest | 6 | 자동 전환 + 진행률 + 시료명 표시 |
| ReleaseControllerTest | 6 | 출고 처리 + 재고 차감 + Negative TC |

---

## 디렉토리 구조

```
ConsoleMVC/
├── ConsoleMVC/          # 메인 프로젝트
│   ├── model/           # 데이터 모델 및 리포지토리 인터페이스
│   │   ├── ISampleRepository.h / IOrderRepository.h  # 인터페이스
│   │   ├── SampleRepository.h/.cpp                   # 인메모리 구현체
│   │   ├── OrderRepository.h/.cpp
│   │   ├── IClock.h / SystemClock.h                  # Clock 추상화
│   │   ├── Sample.h / Order.h / OrderStatus.h
│   ├── view/            # View 인터페이스 및 구현체
│   │   ├── IXxxView.h   # 순수 가상 인터페이스 7개
│   │   └── XxxView.h/.cpp
│   ├── controller/      # Controller
│   │   ├── IController.h
│   │   └── XxxController.h/.cpp
│   └── main.cpp         # 의존성 배선
├── ConsoleMVCTest/      # 테스트 프로젝트 (Google Test)
└── Document/            # 설계 문서
    ├── PRD.md
    ├── FEATURES/
    ├── PHYSICAL_STOCK_CALC.md
    └── WORKLOG.md
```

---

## 관련 문서

| 문서 | 경로 |
|------|------|
| 제품 요구사항 | `Document/PRD.md` |
| 기능 상세 명세 | `Document/FEATURES/FEATURE-0*.md` |
| 물리적 재고 계산 로직 | `Document/PHYSICAL_STOCK_CALC.md` |
| 작업 이력 | `Document/WORKLOG.md` |
