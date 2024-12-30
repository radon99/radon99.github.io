#include <stdio.h>
#include <stdlib.h>

// Task ����ü�� �� W/R ��û�� ��Ÿ���ϴ�.
typedef struct {
    int file_name;     // ���� �̸� �Ǵ� �ĺ���
    int wr;            // 0�̸� ����(Write), 1�̸� �б�(Read)
    int size;          // ������ ũ�� (����Ʈ ����)
    int arrival_time;  // ��û�� ������ �ð� (ns ����)
    int start_time;    // ��û�� ó���Ǳ� ������ �ð� (ns ����)
    int end_time;      // ��û�� �Ϸ�� �ð� (ns ����)
} Task;

// Queue ����ü�� �� �޸� ��ġ�� �۾� ť�� �����մϴ�.
typedef struct {
    Task tasks[10];  // �۾��� �����ϴ� �迭 (���⼭�� �ִ� 10���� �۾��� ť�� ���� ����)
    int front;       // ť�� �պκ� (���� ���� ó���� �۾��� �ε���)
    int rear;        // ť�� �޺κ� (���������� ���� �۾��� �ε���)
} Queue;

// ť �ʱ�ȭ �Լ�
void init_queue(Queue* q) {
    q->front = -1;  // ť�� ��������� ��Ÿ��
    q->rear = -1;   // ť�� ��������� ��Ÿ��
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(Queue* q) {
    return q->front == -1;  // front�� -1�̸� ť�� ��������� �ǹ�
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int is_full(Queue* q) {
    return q->rear == 9;  // rear�� 9�̸� ť�� ���� á���� �ǹ� (���⼭�� ť�� ũ�Ⱑ 10)
}

// ť�� ���ο� �۾��� �߰��ϴ� �Լ�
void enqueue(Queue* q, Task t) {
    if (is_full(q)) {  // ť�� ���� �� ���
        printf("Queue is full!\n");
        return;
    }
    if (is_empty(q)) {  // ť�� ����ִ� ���
        q->front = 0;  // ù ��° �۾��� �߰��Ǹ� front�� 0���� ����
    }
    q->rear++;  // ���ο� �۾��� �߰��ǹǷ� rear�� ����
    q->tasks[q->rear] = t;  // �۾��� ť�� �߰�
}

// ť���� �۾��� �����ϴ� �Լ�
Task dequeue(Queue* q) {
    Task t = { 0 };  // ��� �ִ� �۾��� �ʱ�ȭ
    if (is_empty(q)) {  // ť�� ����ִ� ���
        printf("Queue is empty!\n");
        return t;
    }
    t = q->tasks[q->front];  // ť�� �պκп��� �۾��� ������
    if (q->front >= q->rear) {  // �۾��� ������ �� ť�� ��� �Ǵ� ���
        q->front = q->rear = -1;  // front�� rear�� �ʱ�ȭ�Ͽ� ť�� ���
    }
    else {
        q->front++;  // front�� �������� ���� �۾��� ����Ű���� ��
    }
    return t;  // ���ŵ� �۾��� ��ȯ
}

// PCIe �۾� ť���� �۾��� ó���ϰ� SRAM ť�� �����ϴ� �Լ�
void process_pcieq(Queue* pcieq, Queue* sramq, int global_time, int* sram_wport_busy, int* sram_end_time) {
    if (!is_empty(pcieq) && !(*sram_wport_busy)) {  // PCIe ť�� �۾��� �ְ� SRAM�� �ٻ��� ���� ���
        Task t = pcieq->tasks[pcieq->front];  // PCIe ť�� ù �۾��� ������
        if (t.arrival_time <= global_time) {  // �۾��� ó�� ������ ���� �ð��� �������� Ȯ��
            t.start_time = global_time;  // �۾��� ���۵Ǵ� �ð��� ����
            t.end_time = global_time + 4096;  // SRAM ���� �۾��� ���� �ð��� ���� (��: 4096ns �ҿ�)
            enqueue(sramq, t);  // �۾��� SRAM ť�� �߰�
            *sram_wport_busy = 1;  // SRAM ���� ��Ʈ�� �ٻ����� ����
            *sram_end_time = t.end_time;  // �۾��� �Ϸ�Ǵ� �ð��� ����
            dequeue(pcieq);  // PCIe ť���� �۾� ����
        }
    }
}

// SRAM �۾� ť���� �۾��� ó���ϴ� �Լ�
void process_sramq(Queue* sramq, int* global_time, int* sram_wport_busy, int* sram_end_time) {
    if (!is_empty(sramq)) {  // SRAM ť�� �۾��� �ִ� ���
        Task t = sramq->tasks[sramq->front];  // SRAM ť�� ù �۾��� ������
        if (*global_time >= t.end_time) {  // �۷ι� �ð��� �۾��� ���� �ð��� �����ߴ��� Ȯ��
            *sram_wport_busy = 0;  // �۾��� �Ϸ�Ǿ����Ƿ� SRAM ���� ��Ʈ�� ��� ��
            dequeue(sramq);  // SRAM ť���� �۾� ����
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

        // �۷ι� �ð� ����
        if (sram_wport_busy) {  // SRAM �۾��� ���� ���̸�
            global_time = sram_end_time;  // �۷ι� �ð��� SRAM �۾� ���� �ð����� ����
        }
        else {
            global_time++;  // �׷��� ������ �۷ι� �ð� 1 ����
        }
    }
    printf("Simulation complete at time: %d ns\n", global_time);

    return 0;
}
