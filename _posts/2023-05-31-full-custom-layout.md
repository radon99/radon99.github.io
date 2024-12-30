---
layout: post
category: [hardware, mycad]
title: "풀 커스텀 레이아웃 IC 설계 프로젝트"
date: 2023-05-31
author: jsh
#nextPart: _posts/2024-11-26-building-management.md
#prevPart: _posts/2024-10-23-smart-library.md
---

# 풀 커스텀 레이아웃 IC 설계

이 프로젝트는 MyCAD를 활용한 풀 커스텀 IC 설계 과정을 통해 디지털 집적 회로 설계 및 시뮬레이션을 수행한 내용을 담고 있습니다. 설계 목표는 입력 클럭의 1/8 분주와 입력 신호에 따라 지연된 분주 클럭을 출력하는 회로를 개발하는 것입니다.

---

#과제 내용

입력 클럭 신호의 주파수를 1/8 로 나누어 출력하는 주파수 분주기를 설계한다. 출력 신호는 output clock 과 delayed clock 으로서 두 종류이다. 둘 다 동일한 주파수를 갖고 있지만, delayed clock 은 output clock 보다 n/8x2π 만큼 지연된 신호이다. 입력 클럭 신호는 VDD 와 GND 사이 의 펄스(VPULSE)로 인가한다. 입력 클럭 신호의 rise/fall time 은 각각 period 의 10% 로 설정한
다. 예를 들어, 입력 클럭 신호의 주파수가 100MHz 라면, 주기는 10ns 이고 rise/fall time 은 각 각 1ns 이다. 출력 단에는 아래 그림과 같이 500fF 를 연결한다.

<div style="text-align: center;">
<a href="/assets/img/posts/mycad1.png" data-lity>
  <img src="/assets/img/posts/mycad1.png" style="width: auto; max-height: 500px;" />
</a>
</div>

---
## 주요 설계 과정

### 1. **디자인 아이디어 및 Schematic 설계**
- **1/8 분주기 설계**:

<div style="text-align: center;">
<a href="/assets/img/posts/mycad2.jpg" data-lity>
  <img src="/assets/img/posts/mycad2.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

  - TSPC(True Single Phase Clock) D플립플롭 3개를 비동기적으로 연결하여 설계.
  - TSPC는 높은 주파수에서의 안정성을 제공하기 위해 선택됨.

- **2비트 동등 비교기 설계**:

<div style="text-align: center;">
<a href="/assets/img/posts/mycad0.png" data-lity>
  <img src="/assets/img/posts/mycad0.png" style="width: auto; max-height: 400px;" />
</a>
</div>

<div style="text-align: center;">
<a href="/assets/img/posts/mycad4.png" data-lity>
  <img src="/assets/img/posts/mycad4.png" style="width: auto; max-height: 500px;" />
</a>
</div>

  - 입력 값(Control[1:0])과 TSPC 출력 값을 비교하여 지연 클럭 신호 생성.
  - XNOR 게이트를 Transmission Gate와 Inverter로 구현.

- **2-to-1 MUX 설계**:

<div style="text-align: center;">
<a href="/assets/img/posts/mycad9.jpg" data-lity>
  <img src="/assets/img/posts/mycad9.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

  - Q와 Qbar 출력 신호를 선택하기 위해 사용.
  - NAND 기반으로 변경하여 안정성 강화.

- **최종 Schematic**:

<div style="text-align: center;">
<a href="/assets/img/posts/mycad5.jpg" data-lity>
  <img src="/assets/img/posts/mycad5.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

---

## 시뮬레이션 결과

### 1. **Schematic Simulation**

<div style="text-align: center;">
<a href="/assets/img/posts/mycad6.jpg" data-lity>
  <img src="/assets/img/posts/mycad6.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

- 최대 동작 주파수: **800MHz**
- Delayed Clock 오차 범위: Input Clock 주기의 ±10%

### 2. **Post-Layout Simulation**

<div style="text-align: center;">
<a href="/assets/img/posts/mycad8.jpg" data-lity>
  <img src="/assets/img/posts/mycad8.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

- 최대 동작 주파수: **900MHz**
- Delayed Clock 오차 범위: Input Clock 주기의 ±10%

---

## 레이아웃 설계

### 1. **TSPC 레이아웃**
- 트랜지스터 길이를 일정하게 유지하여 간결한 라우팅 구현.
- 여분 공간에 컨택을 추가하여 기생 커패시턴스 최소화.

### 2. **2비트 비교기 레이아웃**
- XNOR 게이트의 Transmission Gate와 Inverter를 결합하여 면적 최소화.

### 3. **MUX 레이아웃**
- NAND 기반 MUX로 구성. Poly 라인을 Active 주위로 감싸는 방식으로 연결.

### 4. **최종 레이아웃**

<div style="text-align: center;">
<a href="/assets/img/posts/mycad7.jpg" data-lity>
  <img src="/assets/img/posts/mycad7.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

- 카운터(1/8 분주기), 2비트 비교기, MUX, TSPC, 버퍼를 통합.
- 2열 레이아웃 구조로 GND를 결합하여 면적 최적화.

---

## 프로젝트 결과

- **DRC, LVS, ERC** 모두 통과.
- Schematic과 Post-Layout Simulation 간의 최대 동작 주파수 차이를 최소화.
- 안정적이고 효율적인 1/8 분주기 및 지연 클럭 생성 회로 구현.

| 회로 설계   | 시뮬레이션 검증 | 회로도 최대 주파수 | DRC  | LVS  | 포스트 레이아웃 시뮬레이션 검증 | 레이아웃 최대 주파수 | 레이아웃 면적  | GDS 변환 |
|-------------|----------------|--------------------|------|------|------------------------------|----------------------|----------------|----------|
| O           | O              | 800MHz            | O    | O    | O                            | 900MHz              | 1919.7µm²     | O        |


---

## 결론

본 프로젝트를 통해 고주파수 환경에서 안정적으로 동작하는 디지털 회로 설계를 성공적으로 수행하였습니다. 이후 설계에서는 기생 커패시턴스 최소화 및 더 높은 주파수 지원을 위한 최적화 작업을 추가적으로 진행할 필요가 있습니다.

---

## GitHub 저장소
[프로젝트 코드 보기](https://github.com/radon99/radon99.github.io/tree/main/projects/FullCustomLayout)

