#pragma once
#include <stdio.h>
#include <stdlib.h>

#define SRAM_W_D    4096
#define DRAM_W_D    4416
#define NAND_W_D    1402750

typedef struct Task {
    int file_name;     // ���� �̸� �Ǵ� �ĺ���
    int wr;            // 0�̸� ����(Write), 1�̸� �б�(Read)
    int size;          // ������ ũ�� (����Ʈ ����)
    int arrival_time;  // ��û�� ������ �ð� (ns ����)
    int start_time;    // ��û�� ó���Ǳ� ������ �ð� (ns ����)
    int end_time;      // ��û�� �Ϸ�� �ð� (ns ����)
    struct Task* next; // ���� Task�� ����Ű�� ������ (���� ����Ʈ�� ���� ���)
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
