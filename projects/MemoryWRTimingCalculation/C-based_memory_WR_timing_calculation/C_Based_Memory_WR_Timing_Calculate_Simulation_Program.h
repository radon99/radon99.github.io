#pragma once
#include <stdio.h>
#include <stdlib.h>

#define SRAM_W_D    4096
#define DRAM_W_D    4416
#define NAND_W_D    1402750

typedef struct Task {
    int file_name;     // 파일 이름 또는 식별자
    int wr;            // 0이면 쓰기(Write), 1이면 읽기(Read)
    int size;          // 데이터 크기 (바이트 단위)
    int arrival_time;  // 요청이 도착한 시간 (ns 단위)
    int start_time;    // 요청이 처리되기 시작한 시간 (ns 단위)
    int end_time;      // 요청이 완료된 시간 (ns 단위)
    struct Task* next; // 다음 Task를 가리키는 포인터 (연결 리스트를 위해 사용)
} Task;

typedef struct {
    Task* front;
    Task* rear;
} Queue;

//INITIALIZE QUEUE
void init_queue(Queue* q);

//CHECK QUEUE DISABLE
int is_empty(Queue* q);

//ENQUEUE
void enqueue(Queue* q, Task* t);

//DEQUEUE
Task* dequeue(Queue* q);

//PROCESS PCIEQ IN SRAM
void process_pcieq(Queue* pcieq, Queue* sramq, int* global_time, int* sram_wport_busy, int* sram_end_time);

//PROCESS SRAMQ IN DRAM
void process_sramq(Queue* sramq, Queue* dramq, int* global_time, int* dram_wport_busy, int* dram_end_time);

//PROCESS DRAMQ TASK IN NAND
void process_dramq(Queue* dramq, int* global_time, int* nand_wport_busy, int* nand_end_time);
