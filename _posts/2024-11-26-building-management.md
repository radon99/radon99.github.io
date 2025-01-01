---
layout: post
category: [programming, cpp]
title: "IoT BMS 프로젝트"
date: 2024-11-26
author: jsh
excerpt: "RasPi, Arduino, STM32로 구현한 소켓 통신 기반 IoT 건물 관리 시스템 개발"
---

# IoT BMS 프로젝트
<div style="text-align: center;">
<a href="/assets/img/posts/bms_main.png" data-lity>
  <img src="/assets/img/posts/bms_main.png" style="width: auto; max-height: 500px;" />
</a>
</div>

## 개요

### 프로젝트 기간
- 2024.11.22 ~ 2024.11.26

### 목적
STM32, Arduino 그리고 라즈베리파이를 활용한 IoT 기반 빌딩 관리 시스템(BMS)을 구축하여, 다음과 같은 기능을 구현합니다:

- 층별 장치 제어 및 상태 모니터링
- 센서 데이터 수집 및 액츄에이터 제어
- 라즈베리파이를 통한 중앙 관리
- SQL 클라이언트(MariaDB)를 통한 센서값 및 층별 상태 저장
- 소켓 통신으로 명령어 전송

---

## 주요 기능

### 1. 모니터링
- **DHT11 센서**: 실내 온도 및 습도 데이터 측정
- **CDS 센서**: 조도(Light Level) 데이터 측정

### 2. 액추에이터 제어
- **팬 (Fan)**: ON/OFF 제어
- **블라인드 (Blind)**: UP/DOWN 제어
- **램프 (Lamp)**: ON/OFF 제어
- **창문 (Window)**: OPEN/CLOSE 제어

### 3. 알람 기능
- 건물의 개방 시간과 폐쇄 시간을 설정하여 전체 층의 액추에이터를 자동으로 관리

### 4. 앱 제어
- 안드로이드 기반 앱을 통해 전체 층의 액추에이터 조작

---

## 하드웨어 사양

### 구성 요소
- **보드** STM32F4(클라이언트), Arduino Uno(클라이언트), RasPi(서버)
- **센서** DHT11 (온습도), CDS (조도)
- **입출력 장치**
  - 버튼
  - I2C LCD (16x2) 디스플레이
  - 서보 모터 (창문 제어)
  - 스텝 모터 (블라인드 제어)
  - DC모터 및 LED
  
### 하드웨어 구조
<div style="text-align: center;">
<a href="/assets/img/posts/bms3.png" data-lity>
  <img src="/assets/img/posts/bms3.png" style="width: auto; max-height: 300px;" />
</a>
</div>
<div style="text-align: center;">
<a href="/assets/img/posts/bms4.png" data-lity>
  <img src="/assets/img/posts/bms4.png" style="width: auto; max-height: 300px;" />
</a>
</div>

### 연결 다이어그램
- **STM32**
  - GPIO로 LCD 및 버튼 연결
  - Bluetooth 모듈을 통해 통신
- **Arduino**
  - 센서 및 액추에이터와 연결
  - Wi-Fi 모듈을 통해 통신
- **Raspberry Pi**:
  - MySQL 서버와 통신
  - 클라이언트 중계 역할
  
---

## 소프트웨어 구조

### 아키텍처

1. **Application Layer**
   - STM32와 Arduino의 주요 로직을 구현.
   - 모드 전환, 명령 처리, 데이터 송신/수신.
2. **Driver Layer**
   - LCD, 버튼, 서보 모터 등 하드웨어 제어.
3. **Database Integration**
   - SQL 클라이언트와 MySQL 데이터베이스 연동.

---

### 명령어 전달 흐름
**알람 모드 예시**
<div style="text-align: center;">
<a href="/assets/img/posts/bms5.png" data-lity>
  <img src="/assets/img/posts/bms5.png" style="width: auto; max-height: 500px;" />
</a>
</div>

### 주요 명령어 및 동작

#### **STM32 송신**

| **송신 명령어**                      | **설명**                          |
|------------------------------------|----------------------------------|
| `[BMS_SQL]GET@FLOOR@DEVICE`        | 특정 층의 장치 상태 요청.          |
| `[GETTIME]`                        | 현재 시간 요청.                   |
| `[BMS_SQL]SET@FLOOR@DEVICE@STATE`  | 특정 층 장치 상태 설정.            |
| `[BMS_SQL]OPEN` / `[BMS_SQL]CLOSE` | 모든 층 장치를 열림/닫힘 설정.      |

#### **STM32 수신**

| **수신 명령어**                      | **설명**                          |
|------------------------------------|----------------------------------|
| `[BMS_SQL]ACTUATOR@FLOOR@DEVICE@STATE` | 장치 상태 응답.                  |
| `[GETTIME]YYYY-MM-DD-HH-MM-SS`     | 시간 동기화.                      |

#### **Arduino 송신**

| **송신 명령어**                      | **설명**                          |
|------------------------------------|----------------------------------|
| `[BMS_SQL]SENSOR@FLOOR@CDS@HUMI@TEMP` | 센서 데이터 송신.                 |

#### **Arduino 수신**

| **수신 명령어**                      | **설명**                          |
|------------------------------------|----------------------------------|
| `[BMS_%dF]SET@FLOOR@DEVICE@STATE`  | 특정 층 장치 상태 설정.            |

#### **SQL Client 송신**

| **송신 명령어**                      | **설명**                          |
|------------------------------------|----------------------------------|
| `[BMS_SQL]ACTUATOR@FLOOR@DEVICE@STATE` | 장치 상태 응답.                  |
| `[BMS_STM32]SENSOR@FLOOR@CDS@HUMI@TEMP` | 센서 데이터 송신.                 |
| `[BMS_%dF]SET@FLOOR@DEVICE@STATE`  | 특정 층 장치 상태 설정.            |

#### **SQL Client 수신**

| **수신 명령어**                      | **설명**                          |
|------------------------------------|----------------------------------|
| `[BMS_SQL]GET@FLOOR@DEVICE`        | 장치 상태 요청.                   |
| `[BMS_SQL]SET@FLOOR@DEVICE@STATE`  | 특정 층 장치 상태 설정.            |
| `[BMS_SQL]OPEN` / `[BMS_SQL]CLOSE` | 모든 층 장치를 열림/닫힘 설정.      |

---

### 프로젝트 작품
<div style="text-align: center;">
<a href="/assets/img/posts/bms1.png" data-lity>
  <img src="/assets/img/posts/bms1.png" style="width: auto; max-height: 500px;" />
</a>
</div>

---

### 작품 시연 영상
<div style="text-align: center;">
<a href="/assets/img/posts/bms_test.gif" data-lity>
  <img src="/assets/img/posts/bms_test.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
용량 제한으로 인해 영상의 일부 작동 부분만 게시.
 
---

## GitHub 저장소

<div class='sx-button'>
  <a href='https://github.com/radon99/radon99.github.io/tree/main/projects/BuildingManagement' target="_blank">
    <img src='/assets/img/icons/github.png' style="width: auto; max-height: 50px;" />
  </a>
</div>
