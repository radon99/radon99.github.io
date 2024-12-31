---
layout: post
category: [programming, matlab]
title: "임베디드 신호 처리 시스템 프로젝트"
date: 2023-12-14
author: jsh
excerpt: "MATLAB 기반 CMSIS FIR을 활용한 신호 처리 및 분리 시스템 구현"
---

# 임베디드 신호 처리 시스템 프로젝트

<div style="text-align: center;">
<a href="/assets/img/posts/signal_main.png" data-lity>
  <img src="/assets/img/posts/signal_main.png" style="width: auto; max-height: 500px;" />
</a>
</div>

STM32 기반 ARM 프로세서를 사용하여 MATLAB을 활용한 신호 처리와 CMSIS FIR 필터를 적용해 음악 신호를 분리하는 프로젝트입니다.

<div style="text-align: center;">
<a href="/assets/img/posts/signal2.png" data-lity>
  <img src="/assets/img/posts/signal2.png" style="width: auto; max-height: 500px;" />
</a>
</div>

- 블랙핑크의 DDU-DU DDU-DU
- 방탄소년단의 FIRE

이 두 곡이 각각 저역대와 고역대에 위치해있다.

---

## 주요 기능

1. **MATLAB 기반 필터 설계**:
<div style="text-align: center;">
<a href="/assets/img/posts/signal1.jpg" data-lity>
  <img src="/assets/img/posts/signal1.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>
   - Low Pass Filter(LPF)와 High Pass Filter(HPF) 계수를 MATLAB에서 추출.
   - 필터 계수를 CMSIS FIR 구조에 적용.

2. **음악 신호 분리**:
   - 저역대 음악은 LPF를, 고역대 음악은 HPF를 통해 분리.
   - HPF로 분리된 신호는 변조(Modulation)를 통해 저역대로 이동.

3. **CMSIS FIR 필터 적용**:

<div style="text-align: center;">
<a href="/assets/img/posts/signal1.png" data-lity>
  <img src="/assets/img/posts/signal1.png" style="width: auto; max-height: 500px;" />
</a>
</div>

   - ARM Cortex-M4 기반의 CMSIS DSP 라이브러리를 활용하여 FIR 필터를 구현.
   - 왼쪽 채널에 LPF, 오른쪽 채널에 HPF 적용.

---

## 실행 흐름

1. **필터 계수 추출**:
   - MATLAB에서 필터 계수를 소수점 15자리까지 추출.
   - CMSIS FIR 구현에 적용.

2. **FIR 필터 초기화**:
   - LPF와 HPF 각각에 대해 필터 인스턴스 초기화.

3. **모듈레이션**:
   - HPF 출력 신호를 변조하여 저역대로 이동.

4. **테스트 및 결과 확인**:
   - 두 음악 신호를 각각 왼쪽과 오른쪽 채널로 출력.

---

## 과제 의의

- **신호 처리 학습**:
  - FIR 필터와 신호 변조를 활용한 음악 신호 분리 경험.
- **임베디드 DSP 구현**:
  - MATLAB에서 설계한 필터를 실제 하드웨어에 적용.
- **CMSIS DSP 활용**:
  - ARM Cortex-M4 프로세서를 활용하여 효율적인 신호 처리를 구현.

---

## 과제 결과
<div style="text-align: center;">
<a href="/assets/img/posts/signal2.jpg" data-lity>
  <img src="/assets/img/posts/signal2.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>
Output : 두 음악이 합쳐져 있는 출력 spectrogram


<div style="text-align: center;">
<a href="/assets/img/posts/signal3.jpg" data-lity>
  <img src="/assets/img/posts/signal3.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>
DDUDU : Output 출력을 LPF한 출력 spectrogram

<div style="text-align: center;">
<a href="/assets/img/posts/signal4.jpg" data-lity>
  <img src="/assets/img/posts/signal4.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>
Output2 : Output 출력을 HPF한 출력 spectrogram

<div style="text-align: center;">
<a href="/assets/img/posts/signal5.jpg" data-lity>
  <img src="/assets/img/posts/signal5.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>
FIRE : Output2 출력을 shift한 출력 spectrogram

---

## GitHub 저장소

<div class='sx-button'>
  <a href='https://github.com/radon99/radon99.github.io/tree/main/projects/SignalProcessing' target="_blank">
    <img src='/assets/img/icons/github.png' style="width: auto; max-height: 50px;" />
  </a>
</div>



