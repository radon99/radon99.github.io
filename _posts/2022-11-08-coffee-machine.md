---
layout: post
category: [hardware, verilog]
title: "커피 자판기 Verilog 모듈 설계"
date: 2022-11-08
author: jsh
excerpt: "Verilog를 사용하여 Mealy FSM 기반 커피 자판기 설계 및 테스트벤치"
---

# 커피 자판기 Verilog 모듈 설계

<div style="text-align: center;">
<a href="/assets/img/posts/coffee_main.png" data-lity>
  <img src="/assets/img/posts/coffee_main.png" style="width: auto; max-height: 500px;" />
</a>
</div>

이 설계는 FPGA 상에서 작동하는 간단한 커피 자판기 시스템을 구현한 Verilog 모듈입니다. 사용자는 50원, 100원을 입력하고 커피 요청 또는 잔돈 반환을 요구할 수 있으며, 금액 상태와 작동 결과는 LED와 7-세그먼트 디스플레이로 표시됩니다.

---

## 주요 기능

<div style="text-align: center;">
<a href="/assets/img/posts/coffee0.jpg" data-lity>
  <img src="/assets/img/posts/coffee0.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

1. **입력 인터페이스**:
   - **버튼 입력**:
     - `btnU`: 50원 입력.
     - `btnD`: 100원 입력.
     - `btnL`: 커피 요청.
     - `btnR`: 잔돈 반환 요청.
   - **디바운싱 처리**:
     - 모든 버튼 입력에 대해 디바운싱 모듈(`debouncer`)을 사용해 노이즈 제거.

2. **출력 인터페이스**:
   - **LED 출력**:
     - `bypass`: 잔돈 반환.
     - `coff_out`: 커피 제공.
     - `coin_ret`: 잔돈 반환 성공.
   - **7-세그먼트 디스플레이**:
     - 현재 금액을 표시하며, FND 컨트롤러(`fnd_controller`)를 통해 제어.

3. **상태 전이 (FSM)**:
   - 4가지 상태 정의:
     - `EMPTY`: 초기 상태, 금액 없음.
     - `FIFTY`: 50원 입력 상태.
     - `HUND`: 100원 입력 상태.
     - `FIFTY_HUND`: 150원 입력 상태.
   - 상태 전이는 버튼 입력(50원, 100원, 커피 요청, 잔돈 반환)에 따라 변화.

---

## 주요 모듈

### 1. **FSM (Finite State Machine)**
- **상태 레지스터**:
  - 클락(`clk`)과 리셋(`rst`)에 동기화.
- **상태 전이 논리**:
  - 버튼 입력 상태에 따라 다음 상태(`next_state`)를 결정.
- **출력 논리**:
  - 현재 상태와 입력 조건에 따라 LED 출력(`bypass`, `coff_out`, `coin_ret`) 설정.
  - 현재 금액(`amount`) 결정.

### 2. **클락 디바이더**
- 기본 클락(100MHz)을 느린 클락으로 변환하여 FSM의 상태 전이를 제어.

### 3. **FND 컨트롤러**
#### -세그먼트 디코딩
```verilog
always @(*) begin
    case (digit)
        4'd0: seg = 7'b1000000;  // 숫자 0
        4'd1: seg = 7'b1111001;  // 숫자 1
        ...
        default: seg = 7'b1111111;  // 모든 세그먼트 꺼짐
    endcase
end
```

#### -디스플레이 활성화
```verilog
always @(*) begin
    case (digit_select)
        2'b00: digit = value[3:0];    // 첫 번째 자리 (일의 자리)
        2'b01: digit = value[7:4];    // 두 번째 자리 (십의 자리)
        2'b10: digit = value[11:8];   // 세 번째 자리 (백의 자리)
        2'b11: digit = value[15:12];  // 네 번째 자리 (천의 자리)
        default: digit = 4'b0000;
    endcase
end
```
- 현재 금액(`amount`)을 7-세그먼트 디스플레이(`seg`, `an`)에 출력.

### 4. **디바운싱**
```verilog
always @(posedge clk) begin
    if (btn_sync_1 == btn_out) begin
        cnt <= 0;
    end else begin
        cnt <= cnt + 1;
        if (cnt == 20'd1000000) begin
            btn_out <= btn_sync_1;
        end
    end
end
```
-버튼 입력 신호(btn_sync_1)가 출력 신호(btn_out)와 같으면 카운터를 초기화.
-입력 신호가 변경되면 카운터가 동작하며, 일정 시간(1000000 클락 사이클, 약 10ms)이 지나면 새로운 상태를 출력 신호에 반영.
- 버튼 입력 신호를 안정화하여 올바른 동작을 보장.

---

## 주요 코드 설명

### 1. **FSM 상태 전이**
```verilog
always @(*) begin
    if (curr_state == EMPTY) begin
        case({fifty, hundred, cof_out_req, coin_ret_req})
            4'b0100: next_state = HUND;      // 100원 입력
            4'b1000: next_state = FIFTY;     // 50원 입력
            default: next_state = curr_state;
        endcase
    end
    ...
end
```
- 입력 버튼 조합에 따라 다음 상태를 결정.

### 2. **출력 논리**
```verilog
always @(*) begin
    if (curr_state == HUND) begin
        case({fifty, hundred, cof_out_req, coin_ret_req})
            4'b0100: {bypass, coff_out, coin_ret} = 3'b100; // 커피 제공
            default: {bypass, coff_out, coin_ret} = 3'b000; // 대기 상태
        endcase
    end
    ...
end
```
- 현재 상태와 입력 조건에 따라 LED 출력 및 동작을 결정.

### 3. **FND 출력**
```verilog
fnd_controller fnd_inst (
    .value(amount),
    .clk(clk),
    .seg(seg),
    .an(an)
);
```
- 현재 금액(`amount`)을 7-세그먼트 디스플레이로 출력.

---

## Basys3 FPGA

Basys3 FPGA 보드에서 커피 자판기 모듈 테스트를 진행했습니다.

### 1. **설계 파일 준비**
- 모든 Verilog 파일(`coffee_machine.v`, `debouncer.v`, `fnd_controller.v`)과 Basys3 핀 제약 파일(`Basys3_Master.xdc`)을 포함한 프로젝트 생성.
- 핀 매핑:
  - **버튼**:
    - `btnU`: `btn[0]`에 매핑.
    - `btnD`: `btn[1]`에 매핑.
    - `btnL`: `btn[2]`에 매핑.
    - `btnR`: `btn[3]`에 매핑.
  - **LED**:
    - `led[2:0]`에 매핑.
  - **7-세그먼트 디스플레이**:
    - `seg[6:0]`, `an[3:0]` 핀 매핑.

### 2. **FPGA 비트스트림 생성**
- Vivado에서 Synthesis 및 Implementation 완료 후 `.bit` 파일 생성.

### 3. FPGA 프로그래밍
- Basys3 보드를 컴퓨터에 연결.
- Vivado Hardware Manager를 사용하여 .bit 파일을 FPGA에 업로드.

### 4. 테스트 절차
- Basys3 보드의 전원을 켜고 설계된 회로를 FPGA에 프로그래밍.
- 각 버튼의 동작 확인:
  - btnU를 누르면 50원 입력.
  - btnD를 누르면 100원 입력.
  - btnL을 누르면 커피 제공.
  - btnR을 누르면 잔돈 반환.
- 디스플레이 및 LED 확인:
  - 입력 금액이 7-세그먼트 디스플레이에 올바르게 표시되는지 확인.
  - LED 출력(bypass, coff_out, coin_ret)이 동작에 맞게 점등되는지 확인.
  
<div style="text-align: center;">
<a href="/assets/img/posts/coffee_result.gif" data-lity>
  <img src="/assets/img/posts/coffee_result.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
  
---

## 장점 및 개선 가능성

### 장점
- **모듈화**: 디바운싱 및 FND 컨트롤러와 같은 기능이 독립적으로 구현되어 유지보수 용이.
- **확장성**: FSM 상태와 입력 조건을 확장하여 더 복잡한 자판기 기능 추가 가능.

### 개선 가능성
- **테스트 벤치 강화**:
  - 다양한 입력 조합에 대한 포괄적 테스트 필요.
- **상태 추가**:
  - 잔돈 반환 상태나 오류 처리 상태 추가 가능.

---

## GitHub 저장소

<div class='sx-button'>
  <a href='https://github.com/radon99/radon99.github.io/tree/main/projects/CoffeeMachine' target="_blank">
    <img src='/assets/img/icons/github.png' style="width: auto; max-height: 50px;" />
  </a>
</div>
