# IoT 스마트 시스템 프로젝트

이 프로젝트는 블루투스 클라이언트, 층 액추에이터 제어기, IoT 서버 및 STM32 기반 배터리 관리 시스템(BMS) 컨트롤러로 구성된 종합적인 IoT 시스템을 구현합니다.

---

## **프로젝트 구성**

### **1. 블루투스 클라이언트**
- **경로**: `bluetooth_client/`
- **파일**: `iot_client_bluetooth.c`
- **설명**: IoT 디바이스와의 통신을 위한 블루투스 클라이언트 구현.

### **2. 층 액추에이터 제어기**
- **경로**: `floor_actuator_controller/building_floor_controller/`
- **파일**: `building_floor_controller.ino`
- **설명**: Arduino 기반의 건물 층 액추에이터 제어기.

### **3. IoT 서버**
- **경로**: `server/`
- **파일**: `iot_server.c`
- **설명**: IoT 디바이스와 중앙 서버 간 통신을 처리.

### **4. 서버 컨트롤러**
- **경로**: `server_controller/stm32_bms_controller/`
- **주요 파일**:
  - `.cproject`, `.mxproject`, `.ioc`: STM32CubeIDE 프로젝트 설정 파일.
  - `.ld`: STM32 메모리 매핑을 위한 링커 스크립트.
- **설명**: STM32 MCU 기반 배터리 관리 시스템(BMS) 컨트롤러.

---

## **사용 방법**

### **1. 블루투스 클라이언트**
- `iot_client_bluetooth.c` 파일을 컴파일 후 지정된 디바이스에 업로드합니다.
- 코드에서 블루투스 연결 매개변수를 설정합니다.

### **2. 층 액추에이터 제어기**
- `building_floor_controller.ino` 파일을 Arduino IDE에서 엽니다.
- 액추에이터 핀을 설정하고, 마이크로컨트롤러에 업로드합니다.

### **3. IoT 서버**
- `iot_server.c` 파일을 선호하는 C 컴파일러로 컴파일합니다.
- IoT 디바이스 통신을 관리하려면 서버에서 바이너리를 실행합니다.

### **4. 서버 컨트롤러**
- STM32CubeIDE에 `stm32_bms_controller` 프로젝트를 가져옵니다.
- `stm32_bms_controller.ioc` 파일에서 하드웨어 초기화를 설정합니다.
- 펌웨어를 컴파일하고 STM32 디바이스에 업로드합니다.

---

## **필요한 요구사항**

### **개발 도구**
- STM32CubeIDE
- Arduino IDE
- GCC 컴파일러

### **하드웨어**
- STM32F411RE MCU
- 건물 층 관리용 액추에이터 및 센서
- 블루투스 모듈

---
