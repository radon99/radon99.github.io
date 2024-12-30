#include <stdio.h>
#include <stdlib.h>

// Task 구조체는 각 W/R 요청을 나타냅니다.
typedef struct {
    int file_name;     // 파일 이름 또는 식별자
    int wr;            // 0이면 쓰기(Write), 1이면 읽기(Read)
    int size;          // 데이터 크기 (바이트 단위)
    int arrival_time;  // 요청이 도착한 시간 (ns 단위)
    int start_time;    // 요청이 처리되기 시작한 시간 (ns 단위)
    int end_time;      // 요청이 완료된 시간 (ns 단위)
} Task;

// Queue 구조체는 각 메모리 장치의 작업 큐를 관리합니다.
typedef struct {
    Task tasks[10];  // 작업을 저장하는 배열 (여기서는 최대 10개의 작업을 큐에 저장 가능)
    int front;       // 큐의 앞부분 (제일 먼저 처리될 작업의 인덱스)
    int rear;        // 큐의 뒷부분 (마지막으로 들어온 작업의 인덱스)
} Queue;

// 큐 초기화 함수
void init_queue(Queue* q) {
    q->front = -1;  // 큐가 비어있음을 나타냄
    q->rear = -1;   // 큐가 비어있음을 나타냄
}

// 큐가 비어있는지 확인하는 함수
int is_empty(Queue* q) {
    return q->front == -1;  // front가 -1이면 큐가 비어있음을 의미
}

// 큐가 가득 찼는지 확인하는 함수
int is_full(Queue* q) {
    return q->rear == 9;  // rear가 9이면 큐가 가득 찼음을 의미 (여기서는 큐의 크기가 10)
}

// 큐에 새로운 작업을 추가하는 함수
void enqueue(Queue* q, Task t) {
    if (is_full(q)) {  // 큐가 가득 찬 경우
        printf("Queue is full!\n");
        return;
    }
    if (is_empty(q)) {  // 큐가 비어있는 경우
        q->front = 0;  // 첫 번째 작업이 추가되면 front를 0으로 설정
    }
    q->rear++;  // 새로운 작업이 추가되므로 rear를 증가
    q->tasks[q->rear] = t;  // 작업을 큐에 추가
}

// 큐에서 작업을 제거하는 함수
Task dequeue(Queue* q) {
    Task t = { 0 };  // 비어 있는 작업을 초기화
    if (is_empty(q)) {  // 큐가 비어있는 경우
        printf("Queue is empty!\n");
        return t;
    }
    t = q->tasks[q->front];  // 큐의 앞부분에서 작업을 가져옴
    if (q->front >= q->rear) {  // 작업을 제거한 후 큐가 비게 되는 경우
        q->front = q->rear = -1;  // front와 rear를 초기화하여 큐를 비움
    }
    else {
        q->front++;  // front를 증가시켜 다음 작업을 가리키도록 함
    }
    return t;  // 제거된 작업을 반환
}

// PCIe 작업 큐에서 작업을 처리하고 SRAM 큐에 전달하는 함수
void process_pcieq(Queue* pcieq, Queue* sramq, int global_time, int* sram_wport_busy, int* sram_end_time) {
    if (!is_empty(pcieq) && !(*sram_wport_busy)) {  // PCIe 큐에 작업이 있고 SRAM이 바쁘지 않은 경우
        Task t = pcieq->tasks[pcieq->front];  // PCIe 큐의 첫 작업을 가져옴
        if (t.arrival_time <= global_time) {  // 작업이 처리 가능한 도착 시간을 지났는지 확인
            t.start_time = global_time;  // 작업이 시작되는 시간을 설정
            t.end_time = global_time + 4096;  // SRAM 쓰기 작업의 종료 시간을 설정 (예: 4096ns 소요)
            enqueue(sramq, t);  // 작업을 SRAM 큐에 추가
            *sram_wport_busy = 1;  // SRAM 쓰기 포트가 바쁨으로 설정
            *sram_end_time = t.end_time;  // 작업이 완료되는 시간을 설정
            dequeue(pcieq);  // PCIe 큐에서 작업 제거
        }
    }
}

// SRAM 작업 큐에서 작업을 처리하는 함수
void process_sramq(Queue* sramq, int* global_time, int* sram_wport_busy, int* sram_end_time) {
    if (!is_empty(sramq)) {  // SRAM 큐에 작업이 있는 경우
        Task t = sramq->tasks[sramq->front];  // SRAM 큐의 첫 작업을 가져옴
        if (*global_time >= t.end_time) {  // 글로벌 시간이 작업의 종료 시간에 도달했는지 확인
            *sram_wport_busy = 0;  // 작업이 완료되었으므로 SRAM 쓰기 포트가 비게 됨
            dequeue(sramq);  // SRAM 큐에서 작업 제거
        }
    }
}

int main() {
    
    ///INITIALIZE///
    Queue pcieq, sramq;  
    init_queue(&pcieq);  
    init_queue(&sramq);  

    int global_time = 0; 
    int sram_wport_busy = 0;  
    int sram_end_time = 0;  

    ///TASK DEFINE///
    Task t1 = { 3243, 0, 4096, 0, 0, 0 };
    Task t2 = { 101, 0, 4096, 1, 0, 0 };
    Task t3 = { 2222, 0, 4096, 2, 0, 0 };

    ///QUEUE SETTING///
    enqueue(&pcieq, t1);
    enqueue(&pcieq, t2);
    enqueue(&pcieq, t3);

    ///RUN PROGRAM///
    printf("C-based Memory WR Timing Calculate Simulation Program");   

    while (!is_empty(&pcieq) || !is_empty(&sramq) || sram_wport_busy) {
        process_pcieq(&pcieq, &sramq, global_time, &sram_wport_busy, &sram_end_time);
        process_sramq(&sramq, &global_time, &sram_wport_busy, &sram_end_time);

        // 글로벌 시간 관리
        if (sram_wport_busy) {  // SRAM 작업이 진행 중이면
            global_time = sram_end_time;  // 글로벌 시간을 SRAM 작업 종료 시간으로 맞춤
        }
        else {
            global_time++;  // 그렇지 않으면 글로벌 시간 1 증가
        }
    }
    printf("Simulation complete at time: %d ns\n", global_time);

    return 0;
}
