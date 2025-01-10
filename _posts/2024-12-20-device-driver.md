---
layout: post
category: [programming, bsp]
title:  "다중 GPIO와 타이머를 활용한 리눅스 디바이스 드라이버"
date: 2024-12-20
author: jsh
excerpt: "다중 GPIO와 타이머를 활용한 리눅스 디바이스 드라이버 개발"
---

# **다중 GPIO와 타이머를 활용한 리눅스 디바이스 드라이버**

<div style="text-align: center;">
<a href="/assets/img/posts/driver_main.jpg" data-lity>
  <img src="/assets/img/posts/driver_main.jpg" style="width: auto; max-height: 500px;"/>
</a>
</div>

## **프로젝트 개요**

### **목적**
- 리눅스 커널 모듈을 통해 **다중 GPIO 제어**와 **타이머 기반 LED 관리**를 구현.
- 버튼 입력과 키보드 인터페이스를 개선하여 유연한 사용자-커널 상호작용 제공.

### **프로젝트 기간**
- 2024.12.12 ~ 2024.12.20

### **주요 기능**
1. 다중 GPIO 핀 관리 (최대 8개 핀 동시 제어).
2. 커널 타이머를 활용한 LED 점멸.
3. 인터럽트 기반 버튼 입력 처리.
4. IOCTL을 통한 사용자-커널 간 통신.
5. 키보드 입력 및 버튼 이벤트 기반 동작 구현.

---

## **구현 기능**

### **1. 다중 GPIO 관리**
- 각 8개의 GPIO 핀을 배열로 관리하여 LED와 버튼 제어.
- **LED 제어**:
  ```c
  static void gpioLedSet(long val) {
      for (int i = 0; i < GPIOCNT; i++) {
          gpio_set_value(gpioLed[i], (val & (0x01 << i)));
      }
  }
  ```
- **버튼 핀 초기화**:
  ```c
  static int gpioKeyInit(void) {
      for (i = 0; i < GPIOCNT; i++) {
          gpio_request(gpioKey[i], gpioName);
          gpio_direction_input(gpioKey[i]);
      }
  }
  ```

### **2. 커널 타이머 기반 LED 점멸**
- 주기적으로 LED 상태를 반전시키는 타이머 함수.
- 타이머 초기화 및 등록:
  ```c
  void kerneltimer_registertimer(unsigned long timeover) {
      timerLed.expires = get_jiffies_64() + timeover;
      timer_setup(&timerLed, kerneltimer_func, 0);
      add_timer(&timerLed);
  }
  ```
- LED 상태 반전:
  ```c
  void kerneltimer_func(struct timer_list* t) {
      gpioLedSet(ledVal);
      ledVal = ~ledVal & 0xff;
      mod_timer(t, get_jiffies_64() + timerVal);
  }
  ```
  1 jiffies = 10ms 이기 때문에, timer_val = 100은 1초.

### **3. IOCTL 명령 처리**
- 사용자 프로그램과 커널 모듈 간의 통신을 위한 IOCTL 명령 구현.
- 지원되는 명령:
  - `TIMER_START`: 타이머 시작.
  - `TIMER_STOP`: 타이머 중지.
  - `TIMER_VALUE`: 타이머 주기 설정.
- 코드 예시:
  ```c
  static long keyled_ioctl(struct file* filp, unsigned int cmd, unsigned long arg) {
      switch (cmd) {
          case TIMER_START:
              kerneltimer_registertimer(timerVal);
              break;
          case TIMER_STOP:
              del_timer(&timerLed);
              break;
          case TIMER_VALUE:
              copy_from_user(&timerVal, (void*)arg, sizeof(timerVal));
              break;
      }
  }
  ```

### **4. 인터럽트 기반 버튼 입력 처리**
- GPIO 핀에 인터럽트를 등록하여 Rising Edge 발생 시 버튼 입력 처리.
- 동기화를 위해 `mutex_trylock` 사용:
  ```c
  irqreturn_t keyIsr(int irq, void* data) {
      if (mutex_trylock(&keyMutex) != 0) {
          pKeyData->keyNum = i + 1;
          mutex_unlock(&keyMutex);
      }
      wake_up_interruptible(&waitQueueRead);
      return IRQ_HANDLED;
  }
  ```

### **5. 키보드 입력 및 버튼 이벤트 동작**
- 사용자 애플리케이션에서 키보드와 버튼 입력 이벤트를 처리:
  ```c
  ret = poll(Events, 2, 1000);  // dev(버튼)과 stdin(키보드) 대기
  if (Events[0].revents & POLLIN) {  // 버튼 입력 이벤트
      read(dev, &key_no, sizeof(key_no));
      switch (key_no) {
          case 1:
              ioctl(dev, TIMER_STOP);
              break;
          case 4:
              ioctl(dev, TIMER_START);
              break;
          case 8:
              loopFlag = 0;  // 종료
              break;
      }
  }
  if (Events[1].revents & POLLIN) {  // 키보드 입력 이벤트
      fgets(inputString, sizeof(inputString), stdin);
      if (key_no == 2) {
          timer_val = atoi(inputString);
          ioctl(dev, TIMER_VALUE, &info);
      }
  }
  ```

---

## **디렉토리 구조**

<div style="display: flex; justify-content: center; align-items: center; flex-direction: column; font-family: monospace;">
  <pre style="text-align: left;">
kerneltimer
├── driver               # 디바이스 드라이버 코드
│   ├── ioctl_test.h     # IOCTL 명령 정의
│   └── kerneltimer_dev.c # 커널 모듈 구현
└── app                  # 사용자 애플리케이션 코드
    └── kerneltimer_app.c # IOCTL 호출 및 이벤트 처리
  </pre>
</div>

---

## **빌드 및 실행**

### **빌드 환경**
- **운영체제**: Ubuntu 20.04 LTS
- **크로스 컴파일러**: ARM GNU Toolchain
- **프로그래밍 언어**: C
- **도구**: Makefile

### **빌드 및 실행**
1. **드라이버 빌드**:
   ```bash
   make
   ```
2. **드라이버 로드**:
   ```bash
   sudo mknod /dev/keyled_dev c 230 0
   sudo chmod 666 /dev/keyled_dev
   sudo insmod kerneltimer_dev.ko
   ```
3. **사용자 애플리케이션 실행**:
   ```bash
   ./kerneltimer_app 0xff 100  # LED 값과 타이머 값 전달
   ```
4. **IOCTL 명령 테스트**:
   - 버튼 입력 처리:
     - 버튼 1: 타이머 중지.
     - 버튼 2: 키보드 입력을 통한 타이머 주기 설정
     - 버튼 3: 타이머 시작.
     - 버튼 4: 애플리케이션 종료.
     
---

## **작동영상**
<div style="text-align: center;">
<a href="/assets/img/posts/driver_result.gif" data-lity>
  <img src="/assets/img/posts/driver_result.gif" style="width: auto; max-height: 500px;"/>
</a>
</div>

---

## **결론**

이 프로젝트는 LED와 버튼 GPIO와 커널 타이머, 인터럽트를 활용한 디바이스 드라이버를 구현하며, 사용자 애플리케이션은 키보드와 버튼 이벤트를 처리합니다. 이를 통해 리눅스 디바이스 드라이버와 사용자 프로그램 간의 상호작용을 강화했습니다.

---

## **GitHub 저장소**

<div class='sx-button'>
  <a href='https://github.com/radon99/radon99.github.io/tree/main/projects/DeviceDriver' target="_blank">
    <img src='/assets/img/icons/github.png' style="width: auto; max-height: 50px;" />
  </a>
</div>


