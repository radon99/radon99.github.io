---
layout: post
category: [programming, python]
title: "Smart Library 프로젝트"
date: 2024-10-23
author: jsh
nextPart: _posts/2024-11-26-building-management.md
prevPart: _posts/2024-09-05-focus-me.md
---

# 스마트 도서 관리 시스템
<div style="text-align: center;">
<a href="/assets/img/posts/booktell.jpg" data-lity>
  <img src="/assets/img/posts/booktell.jpg" style="width: auto; max-height: 500px;" />
</a>
</div>

## **개요**
이 프로젝트는 도서관 관리 효율성을 높이고 이용자 편의를 증대시키기 위해 설계되었습니다. AI 기반 시스템을 활용하여 도서 위치 추적 및 자동화된 관리 서비스를 제공합니다.

### **프로젝트 기간**
- 2024.09.26 ~ 2024.10.23


### **개발 일정**
<div style="text-align: center;">
<a href="/assets/img/posts/WBS.png" data-lity>
  <img src="/assets/img/posts/WBS.png" style="width: auto; max-height: 500px;" />
</a>
</div>

---

## **주요 기능**

1. **책장 상태 동기화**:
   - 도서관 책장의 데이터를 실시간으로 데이터베이스와 동기화합니다.
2. **도서 위치 추적**:
   - 특정 책의 위치를 실시간으로 확인하여 업무 효율성을 높입니다.
3. **챗봇**:
   - 도서관 관련 질의 응답 및 건의사항 전달을 지원합니다.
4. **AI 기반 정렬**:
   - 책이 혼란스럽게 배치된 경우 AI가 책의 위치를 알려줍니다.

---

## **활용 사례**
1. **작은 도서관 관리**:
   - 사서가 없는 도서관의 운영 효율성을 극대화.
2. **도서관 방문자 경험 개선**:
   - 이용자가 챗봇을 통해 쉽게 필요한 정보를 얻을 수 있음.
3. **업무 경감**:
   - 사서의 반복 업무를 줄이고 핵심 업무에 집중할 수 있도록 지원.

---

## **프로그램 구성**

<div style="text-align: center;">
<a href="/assets/img/posts/high_level_diagram.bmp" data-lity>
  <img src="/assets/img/posts/high_level_diagram.bmp" style="width: auto; max-height: 500px;" />
</a>
</div>

---

## 프로그램 흐름

1. **시작**: 두 개의 카메라(Cam1, Cam2)에서 각각 프레임을 캡처.
2. **프레임 전송**: 캡처한 프레임은 각각 `widget_cam_1_queue`와 `widget_cam_2_queue`로 전송.
3. **UI 데이터 처리**: UI_Process에서 영상 데이터를 처리.
4. **책 상태 확인 요청**: 책의 상태 확인을 요청.
5. **상태 확인**: 
   - 책 상태 확인

		1. Yolo 모델을 이용한 책 검출
		
		2. PaddleOCR 모델을 이용한 책 정보 추출
		
		3. OCR 텍스트와 도서 목록 리스트와 유사도 비교
   - 책 배치 상태 확인
   
		LIS 알고리즘을 이용한 오배치 도서 판단을 위한 알고리즘
6. **유효성 검사**:
   - 책 상태가 유효한 경우 상태를 업데이트하고 저장한 후 UI를 통해 결과를 표시.
   - 유효하지 않은 경우 책 상태를 다시 확인.
7. **종료**: 처리 완료 후 흐름 종료.

---

## **기능 설계**

### **1. Yolo 모델 파인튜닝**
<div style="text-align: center;">
<a href="/assets/img/posts/yolo.png" data-lity>
  <img src="/assets/img/posts/yolo.png" style="width: auto; max-height: 500px;" />
</a>
</div>
책의 ‘등’ 윤곽선이 필요하기 때문에 최적화를 위해 파인튜닝하였습니다.

<div style="text-align: center;">
<a href="/assets/img/posts/yolo_result.png" data-lity>
  <img src="/assets/img/posts/yolo_result.png" style="width: auto; max-height: 500px;" />
</a>
</div>
크롭된 이미지들은 객체 인식 오류 없이 매끄러운 경계로 추출되었습니다.

### **2. PaddleOCR 모델 책표지 텍스트 파인튜닝**
<div style="text-align: center;">
<a href="/assets/img/posts/ocr_pretrain.png" data-lity>
  <img src="/assets/img/posts/ocr_pretrain.png" style="width: auto; max-height: 500px;" />
</a>
</div>
AI_hub 사이트의 학습 데이터를 이용하여 PaddleOCR 모델에 맞는 이미지 전처리하였습니다.

<div style="text-align: center;">
<a href="/assets/img/posts/ocr_result.png" data-lity>
  <img src="/assets/img/posts/ocr_result.png" style="width: auto; max-height: 500px;" />
</a>
</div>
파인튜닝한 모델이 책표지 텍스트 인식에 더 강인하였습니다.

### **3. 도서 상태 기능 작동 테스트**
<div style="text-align: center;">
<a href="/assets/img/posts/function_test.png" data-lity>
  <img src="/assets/img/posts/function_test.png" style="width: auto; max-height: 500px;" />
</a>
</div>
QT를 이용하여 간단한 테스트용 GUI 구성 및 단일 카메라로 테스트하였습니다.

---

## **프로젝트 결과**

### **1. 메인 프로그램**
<div style="text-align: center;">
<a href="/assets/img/posts/MainProgram.gif" data-lity>
  <img src="/assets/img/posts/MainProgram.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
- 로그인 후 메인 화면에서 책장 2개를 실시간으로 감지하고 상태를 표시합니다.

---

### **2. 챗봇**
<div style="text-align: center;">
<a href="/assets/img/posts/chatbot.gif" data-lity>
  <img src="/assets/img/posts/chatbot.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
- Flask 기반으로 PC 및 모바일에서 동작하며, 도서관 건의사항 접수 및 질문 응답을 제공합니다.

---

### **3. 건의사항 기능**
<div style="text-align: center;">
<a href="/assets/img/posts/suggestions.gif" data-lity>
  <img src="/assets/img/posts/suggestions.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
- 건의사항은 Main Program에서 실시간으로 확인 가능하며, Cam 2번을 통해 사용자 동작을 시각화합니다.

---

### **4. 신간 등록**
<div style="text-align: center;">
<a href="/assets/img/posts/addnewbooks.gif" data-lity>
  <img src="/assets/img/posts/addnewbooks.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
<div style="text-align: center;">
<a href="/assets/img/posts/addnewbooks_db.gif" data-lity>
  <img src="/assets/img/posts/addnewbooks_db.gif" style="width: auto; max-height: 500px;" />
</a>
</div>
- 사서가 엑셀 파일을 업로드하여 신간 도서를 데이터베이스에 자동으로 추가합니다.

---

## **요구 사항**

### **하드웨어**
- 웹캠.

### **소프트웨어**
- Python 3.7 이상
- 필수 라이브러리:
  - OpenCV
  - Flask
  - PaddleOCR

---

## **향후 개선 방향**
1. **PaddleOCR 모델 개선**:
   - 도서 제목 인식 정확도 향상.
2. **챗봇 기능 확장**:
   - 자연어 처리(NLP) 기반의 더 나은 응답 제공.
3. **도서 위치 추적 정밀도 개선**:
   - AI 모델 최적화를 통해 정확도 향상.

---

## **GitHub 저장소**
[프로젝트 코드 보기](https://github.com/radon99/radon99.github.io/smartlibrary)

