# 물리적 재고 계산 로직

## 개요

본 시스템에서 "재고"는 두 가지로 구분된다.

| 구분 | 설명 |
|------|------|
| **보유 재고** (`sample.stock`) | DB에 저장된 실제 수치. 출고(RELEASE) 시 차감되고, 생산 완료(PRODUCING → CONFIRMED) 시 증가한다. |
| **물리적 재고(실시간)** | 승인 시 재고 충분 여부를 판단하기 위해 계산하는 값. 보유 재고에 현재 생산 진행분을 더한다. |

---

## 물리적 재고 계산 공식

```
물리적 재고(실시간) = 보유 재고 + Σ (PRODUCING 주문의 실생산량 × 진행률)
```

### 진행률 계산

```
진행률 = min(1.0, 경과 시간(초) / 전체 생산 시간(초))
전체 생산 시간(초) = totalProductionTimeMin × 60
경과 시간(초) = 현재 시각 - productionStartTime
```

### 예시

| 항목 | 값 |
|------|-----|
| 보유 재고 | 10 ea |
| PRODUCING 주문 실생산량 | 100 ea |
| 전체 생산 시간 | 200분 (12,000초) |
| 경과 시간 | 6,000초 |
| 진행률 | 6,000 / 12,000 = 0.5 (50%) |
| **물리적 재고** | **10 + 100 × 0.5 = 60 ea** |

---

## 재고 변동 시점 정책

| 이벤트 | 처리 |
|--------|------|
| 주문 승인 → CONFIRMED (재고 충분) | 재고 변동 없음 |
| 주문 승인 → PRODUCING (재고 부족) | 재고 변동 없음. productionStartTime 기록 |
| 생산 완료 (PRODUCING → CONFIRMED) | `sample.stock += actualProduction` (increaseStock) |
| 출고 처리 (CONFIRMED → RELEASE) | `sample.stock -= order.quantity` (decreaseStock) |

---

## 실생산량 계산 공식

주문 수량 대비 재고가 부족할 때 생산해야 할 수량:

```
실생산량 = ceil(부족분 / (수율 × 0.9))
```

- `부족분` = 주문 수량 - 물리적 재고
- `수율` = 정상 생산 비율 (0~1)
- `× 0.9` = 10% 공정 오차 보정 (SPEC 명시)

### 예시

| 항목 | 값 |
|------|-----|
| 주문 수량 | 200 ea |
| 물리적 재고 | 30 ea |
| 부족분 | 170 ea |
| 수율 | 0.92 |
| **실생산량** | **ceil(170 / (0.92 × 0.9)) = ceil(205.31) = 206 ea** |

---

## 구현 위치

| 로직 | 파일 |
|------|------|
| 물리적 재고 계산 | `controller/ApprovalController.cpp` |
| 실생산량 공식 | `controller/ApprovalController.cpp` |
| 생산 완료 자동 전환 + increaseStock | `controller/ProductionLineController.cpp` |
| 출고 시 decreaseStock | `controller/ReleaseController.cpp` |
| Clock 인터페이스 | `model/IClock.h` |
