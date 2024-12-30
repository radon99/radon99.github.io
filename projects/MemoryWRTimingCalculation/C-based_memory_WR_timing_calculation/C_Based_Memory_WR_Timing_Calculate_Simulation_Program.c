#include "C_Based_Memory_WR_Timing_Calculate_Simulation_Program.h"

//INITIALIZE QUEUE
void init_queue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

//CHECK QUEUE DISABLE
int is_empty(Queue* q) {
    return (q->front == NULL);
}

//ENQUEUE
void enqueue(Queue* q, Task* t) {
    if (is_empty(q)) {
        q->front = q->rear = t;
    }
    else {
        q->rear->next = t;
        q->rear = t;
    }
    q->rear->next = NULL;
}

//DEQUEUE
Task* dequeue(Queue* q) {
    if (!is_empty(q)) {
        Task* t = q->front;
        q->front = q->front->next;
        if (q->front == NULL) {
            q->rear = NULL;
        }
        return t;
    }
    else {
        printf("Queue is empty!\n");
        return NULL;
    }
}

//PROCESS PCIEQ IN SRAM
void process_pcieq(Queue* pcieq, Queue* sramq, int* global_time, int* sram_wport_busy, int* sram_end_time) {
    if (!is_empty(pcieq) && !(*sram_wport_busy)) {
        Task* t = pcieq->front;
        if (t->arrival_time <= *global_time) {
            t->start_time = *global_time;
            t->end_time = *global_time + SRAM_W_D;
            *sram_wport_busy = 1;
            *sram_end_time = t->end_time;
            printf("%8d파일 SRAM 작업 시작: %8d ns\n", t->file_name, *global_time);
        }
    }

    if (*sram_wport_busy && *sram_end_time <= *global_time) {
        *sram_wport_busy = 0;
        if (!is_empty(pcieq)) {
            Task* t = dequeue(pcieq);  //BUG FIX CODE
            enqueue(sramq, t);         
            printf("%8d파일 SRAM 작업 완료: %8d ns\n", t->file_name, *global_time);
            if (is_empty(pcieq))
                printf("        SRAM 전체 작업 완료: %8d ns\n", *global_time);
        }
    }
}

//PROCESS SRAMQ IN DRAM
void process_sramq(Queue* sramq, Queue* dramq, int* global_time, int* dram_wport_busy, int* dram_end_time) {
    if (!is_empty(sramq) && !(*dram_wport_busy)) {
        Task* t = sramq->front;
        if (*global_time >= t->end_time) {
            t->start_time = *global_time;
            t->end_time = *global_time + DRAM_W_D;
            *dram_wport_busy = 1;
            *dram_end_time = t->end_time;
            printf("%8d파일 DRAM 작업 시작: %8d ns\n", t->file_name, *global_time);
        }
    }

    if (*dram_wport_busy && *dram_end_time <= *global_time) {
        *dram_wport_busy = 0;
        Task* t = dequeue(sramq);
        enqueue(dramq, t);
        printf("%8d파일 DRAM 작업 완료: %8d ns\n", t->file_name, *global_time);
        if (is_empty(sramq))
            printf("        DRAM 전체 작업 완료: %8d ns\n", *global_time);
    }
}

//PROCESS DRAMQ TASK IN NAND
void process_dramq(Queue* dramq, int* global_time, int* nand_wport_busy, int* nand_end_time) {
    if (!is_empty(dramq) && !(*nand_wport_busy)) {
        Task* t = dramq->front;
        if (*global_time >= t->end_time) {
            t->start_time = *global_time;
            t->end_time = *global_time + NAND_W_D;
            *nand_wport_busy = 1;
            *nand_end_time = t->end_time;
            printf("%8d파일 NAND 작업 시작: %8d ns\n", t->file_name, *global_time);
        }
    }

    if (*nand_wport_busy && *nand_end_time <= *global_time) {
        *nand_wport_busy = 0;
        Task* t = dequeue(dramq);
        printf("%8d파일 NAND 작업 완료: %8d ns\n", t->file_name, *global_time);
        if (is_empty(dramq))
            printf("        NAND 전체 작업 완료: %8d ns\n", *global_time);
    }
}

int main() {
    ///INITIALIZE///
    Queue pcieq, sramq, dramq;
    init_queue(&pcieq);
    init_queue(&sramq);
    init_queue(&dramq);

    int global_time = 0;
    int sram_wport_busy = 0, dram_wport_busy = 0, nand_wport_busy = 0;
    int sram_end_time = 0, dram_end_time = 0, nand_end_time = 0;

    ///TASK DEFINE///
    Task* t1 = (Task*)malloc(sizeof(Task));
    Task* t2 = (Task*)malloc(sizeof(Task));
    Task* t3 = (Task*)malloc(sizeof(Task));

    *t1 = (Task){ 3243, 0, 4096, 0, 0, 0, NULL };
    *t2 = (Task){ 101, 0, 4096, 1, 0, 0, NULL };
    *t3 = (Task){ 2222, 0, 4096, 2, 0, 0, NULL };

    ///ADD QUEUE///
    enqueue(&pcieq, t1);
    enqueue(&pcieq, t2);
    enqueue(&pcieq, t3);

    ///PROGRAM RUNNING///
    printf("////C-based Memory WR Timing Calculate Simulation Program////\n");

    while (!is_empty(&pcieq) || !is_empty(&sramq) || !is_empty(&dramq) || nand_wport_busy) {
        process_pcieq(&pcieq, &sramq, &global_time, &sram_wport_busy, &sram_end_time);
        process_sramq(&sramq, &dramq, &global_time, &dram_wport_busy, &dram_end_time);
        process_dramq(&dramq, &global_time, &nand_wport_busy, &nand_end_time);
        global_time++;
    }
    printf("\n     모든 작업 처리완료시간: %8d ns\n", global_time);

    ///QUEUE DISABLE///
    free(t1);
    free(t2);
    free(t3);

    return 0;
}
