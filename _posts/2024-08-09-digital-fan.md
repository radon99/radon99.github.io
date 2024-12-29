---
layout: post
category: [programming, cpp]
title:  "Digital Fan 프로젝트"
date: 2024-08-09
author: jsh #Author's nick.
nextPart: _posts/2024-09-05-focus-me.md #Next part.
---

# **Digital Fan 프로젝트**
<div style="text-align: center;">
<a href="/assets/img/posts/DigitalFan_main.jpg" data-lity>
  <img src="/assets/img/posts/DigitalFan_main.jpg" style="width: auto; max-height: 500px;"/>
</a>
</div>



## 개요


### 프로젝트 기간
- 2024.07.23 ~ 2024.08.09



### 목적
ATmega128 마이크로컨트롤러를 기반으로 설계된 선풍기 제어 시스템으로, 다음과 같은 기능을 포함합니다:

- 자동/수동 모드 전환 및 풍속 제어
- 타이머 설정 기능
- 부저를 활용한 음악 재생

---

## 주요 기능

1. **자동 모드**: 자연풍을 구현하여 선풍기 속도 자동 조절
2. **수동 모드**: 사용자가 직접 풍속(저속, 중속, 고속) 및 타이머 설정
3. **디스플레이 출력**:
   - 16x2 LCD를 통해 현재 모드와 상태 표시
   - 7-세그먼트 디스플레이(FND)를 통해 남은 시간 표시
4. **UART 제어**: 직렬 통신을 통한 외부 명령 수신 및 제어
5. **부저 음악 재생**: 바람 세기에 따른 음악 속도 조절 및 재생

---

## 하드웨어 사양


### 구성 요소
- **MCU**: ATmega128 (16MHz 클럭)
- **입력 장치**: 버튼, UART
- **출력 장치**:
  - 16x2 LCD
  - 7-세그먼트 디스플레이(FND)
  - DC 모터
  - 부저
- **제어 방식**: PWM을 활용한 선풍기 속도 제어


### 연결 다이어그램
- **버튼**: GPIO 핀 연결, Pull-up 방식
- **LCD**: 데이터 핀 8개 및 제어 핀 3개로 병렬 연결
- **FND**: 공통 캐소드 방식, 병렬 연결
- **UART**: TX, RX 핀을 통해 직렬 USB 터미널 연결

---

## 소프트웨어 구조


### 계층형 아키텍처
<div style="text-align: center;">
<a href="/assets/img/posts/sw_stack.jpg" data-lity>
  <img src="/assets/img/posts/sw_stack.jpg" style="width: auto; max-height: 500px;"/>
</a>
</div>


1. **Application Layer**:
   - 메인 로직, 입력 처리, 데이터 관리, 디스플레이 갱신
2. **Driver Layer**:
   - 하드웨어 장치(Button, LCD, FND, Buzzer)의 추상화된 인터페이스 제공
3. **Peripheral Layer**:
   - GPIO, 타이머, UART 등의 저수준 하드웨어 제어

### 주요 소프트웨어 기능
<div style="text-align: center;">
<a href="/assets/img/posts/fsm.jpg" data-lity>
  <img src="/assets/img/posts/fsm.jpg" style="width: auto; max-height: 500px;"/>
</a>
</div>


1. **시스템 초기화**
   - GPIO, 타이머, LCD, FND, UART, 부저 초기화

2. **입력 처리**
   - 버튼 : GPIO 핀에 연결하여 디바운싱 입력 처리, 눌림/떼어짐 구현
   - UART : 명령을 통해 모드 전환 및 설정 변경

3. **모드 전환**
   - 자동 모드: 66~100% 범위의 랜덤한 Duty Cycle로 자연풍 구현
   - 수동 모드: 사용자가 직접 풍속 조절 및 타이머 설정

4. **디스플레이 갱신**
   - LCD에 현재 상태 출력, 타이머 구동시 제품명 바운스 기능(1초마다 1칸씩 이동), 타이머 구동하지 않을 때는 제품명 가운데 정렬
   - FND에 남은 시간 또는 풍속 표시

5. **PWM 기반 속도 제어**
   - Prescaler 1/64 설정
   - FAST PWM 모드, 비반전 모드

6. **부저 음악 재생**
   - 주파수를 조합하여 음악 배열 구성
   - 바람 세기에 따라 음 유지 시간 조정
   - 음 사이에 300ms 간격 유지

---

## 빌드 및 실행

### 빌드 환경
- **운영체제**: Windows 10 x64
- **프로그래밍 언어**: C
- **컴파일러**: AVR GCC
- **IDE**: Microchip Studio

### 실행 방법
1. 프로젝트를 빌드하여 HEX 파일 생성
2. ATmega128에 업로드
3. 보드 전원을 연결하여 실행
4. 버튼으로 모드 및 설정 변경

---

## LCD 출력화면 예시

1. 타이머 종료
     ```
     Digital Fan!
     STOP  00:00
     ```
	 
2. 타이머 작동
     ```
     Digital Fan!
     LOW   02:57
     ```

3. 수동 모드
     ```
     Digital Fan!
     LOW   00:00
     ```
	 
4. 오토 모드
     ```
     Digital Fan!
     AUTO  00:00
     ```
	 
---

## 프로젝트 디렉토리 구조
<div style="text-align: center;">
<a href="/assets/img/posts/sw_architecture.jpg" data-lity>
  <img src="/assets/img/posts/sw_architecture.jpg" style="width: auto; max-height: 500px;"/>
</a>
</div>

<div style="display: flex; justify-content: center; align-items: center; flex-direction: column; font-family: monospace;">
  <pre style="text-align: left;">
DigitalFan
├── AP                  # 애플리케이션 계층
│   ├── apMain.c       # 메인 로직
│   ├── Listener       # 입력 처리
│   ├── Model          # 데이터 관리
│   ├── Presenter      # 디스플레이 관리
│   └── Service        # 선풍기 제어
├── driver              # 하드웨어 드라이버
│   ├── Button         # 버튼 입력 처리
│   ├── FND            # 7-세그먼트 디스플레이
│   ├── LCD            # LCD 디스플레이
│   └── Buzzer         # 부저 음악 재생
├── periph              # 주변 장치
│   ├── GPIO           # GPIO 제어
│   ├── TIM            # 타이머 관리
│   └── UART0          # UART 통신
├── Debug               # 빌드된 실행 파일
└── README.md           # 프로젝트 설명
  </pre>
</div>

---

## 참고 자료
- [ATmega128 데이터시트](https://ww1.microchip.com/downloads/en/devicedoc/atmel-8151-8-bit-avr-atmega128_datasheet.pdf)

---

## GitHub 저장소
[프로젝트 코드 보기](https://github.com/radon99/radon99.github.io/tree/main/projects/DigitalFan)


