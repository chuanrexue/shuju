#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARKING_SIZE 3   // 停车场最多容纳3辆车

// 车辆信息
typedef struct Car {
    char license[10];    // 车牌号（简单字符串）
    struct Car *next;    // 用于队列的指针
} Car;

// ---------- 栈（停车场）----------
typedef struct {
    Car *data[PARKING_SIZE];  // 栈数组，存放Car指针
    int top;                  // 栈顶指针（-1表示空）
} ParkingStack;

// ---------- 队列（便道）----------
typedef struct {
    Car *front;   // 队头指针
    Car *rear;    // 队尾指针
    int count;    // 元素个数（可选，方便判空）
} WaitQueue;

// 全局变量
ParkingStack parking;
WaitQueue waiting;

// ========== 函数声明 ==========
// 栈操作
void initParking(ParkingStack *s);
int isParkingFull(ParkingStack *s);
int isParkingEmpty(ParkingStack *s);
void pushParking(ParkingStack *s, Car *car);
Car* popParking(ParkingStack *s);
Car* topParking(ParkingStack *s);

// 队列操作
void initWaiting(WaitQueue *q);
int isWaitingEmpty(WaitQueue *q);
void enqueueWaiting(WaitQueue *q, Car *car);
Car* dequeueWaiting(WaitQueue *q);

// 辅助函数
int isCarInParking(ParkingStack *s, char *license);
int isCarInWaiting(WaitQueue *q, char *license);
int findCarInParking(ParkingStack *s, char *license);

// 核心功能
void arrive(char *license);
void leave(char *license);
void showParking();
void showWaiting();
void freeAll();

// ========== 栈操作实现 ==========
void initParking(ParkingStack *s) {
    s->top = -1;  // 初始化栈顶为-1，表示空栈
}

int isParkingFull(ParkingStack *s) {
    return s->top == PARKING_SIZE - 1;  // 栈顶等于最大下标则满
}

int isParkingEmpty(ParkingStack *s) {
    return s->top == -1;  // 栈顶为-1则空
}

void pushParking(ParkingStack *s, Car *car) {
    if (isParkingFull(s)) {
        printf("停车场已满，无法停车！\n");
        return;
    }
    s->data[++s->top] = car;  // 栈顶上移，存入车辆
}

Car* popParking(ParkingStack *s) {
    if (isParkingEmpty(s)) {
        return NULL;
    }
    return s->data[s->top--];  // 返回栈顶元素，栈顶下移
}

Car* topParking(ParkingStack *s) {
    if (isParkingEmpty(s)) {
        return NULL;
    }
    return s->data[s->top];  // 仅返回，不修改栈
}

// ========== 队列操作实现 ==========
void initWaiting(WaitQueue *q) {
    q->front = q->rear = NULL;
    q->count = 0;
}

int isWaitingEmpty(WaitQueue *q) {
    return q->count == 0;
}

void enqueueWaiting(WaitQueue *q, Car *car) {
    car->next = NULL;
    if (isWaitingEmpty(q)) {
        // 空队列，头尾都指向新节点
        q->front = q->rear = car;
    } else {
        // 非空，尾节点后接新节点，更新尾指针
        q->rear->next = car;
        q->rear = car;
    }
    q->count++;
}

Car* dequeueWaiting(WaitQueue *q) {
    if (isWaitingEmpty(q)) {
        return NULL;
    }
    Car *temp = q->front;
    q->front = q->front->next;  // 头指针后移
    q->count--;
    
    // 出队后队列为空，尾指针置空
    if (isWaitingEmpty(q)) {
        q->rear = NULL;
    }
    return temp;
}

// ========== 辅助函数实现 ==========
int isCarInParking(ParkingStack *s, char *license) {
    for (int i = 0; i <= s->top; i++) {
        if (strcmp(s->data[i]->license, license) == 0) {
            return 1;
        }
    }
    return 0;
}

int isCarInWaiting(WaitQueue *q, char *license) {
    Car *p = q->front;
    while (p != NULL) {
        if (strcmp(p->license, license) == 0) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int findCarInParking(ParkingStack *s, char *license) {
    for (int i = 0; i <= s->top; i++) {
        if (strcmp(s->data[i]->license, license) == 0) {
            return i;
        }
    }
    return -1;
}

// ========== 核心功能实现 ==========
void arrive(char *license) {
    // 检查车辆是否已存在
    if (isCarInParking(&parking, license) || isCarInWaiting(&waiting, license)) {
        printf("车辆已在系统中！\n");
        return;
    }

    // 创建新车节点
    Car *newCar = (Car*)malloc(sizeof(Car));
    strcpy(newCar->license, license);
    newCar->next = NULL;

    // 停车场未满，直接停车
    if (!isParkingFull(&parking)) {
        pushParking(&parking, newCar);
        printf("车辆 %s 已停入停车场（车位%d）\n", license, parking.top + 1);
    } else {
        // 停车场满，进入便道
        enqueueWaiting(&waiting, newCar);
        printf("停车场已满，车辆 %s 进入便道等待\n", license);
    }
}

void leave(char *license) {
    // 1. 查找车辆位置
    int pos = findCarInParking(&parking, license);
    if (pos == -1) {
        printf("未找到车辆 %s！\n", license);
        return;
    }

    // 2. 暂存目标车辆上方的所有车辆
    Car *tempStack[PARKING_SIZE];
    int tempCount = 0;
    while (parking.top > pos) {
        tempStack[tempCount++] = popParking(&parking);
    }

    // 3. 目标车辆离开
    Car *target = popParking(&parking);
    printf("车辆 %s 离开，", target->license);
    free(target);

    // 4. 临时栈车辆重新停入停车场
    for (int i = tempCount - 1; i >= 0; i--) {
        pushParking(&parking, tempStack[i]);
    }
    printf("其后车辆重新停入\n");

    // 5. 便道有车则补入停车场
    if (!isWaitingEmpty(&waiting)) {
        Car *waitCar = dequeueWaiting(&waiting);
        pushParking(&parking, waitCar);
        printf("便道车辆 %s 进入停车场\n", waitCar->license);
    }
}

void showParking() {
    if (isParkingEmpty(&parking)) {
        printf("停车场为空\n");
        return;
    }
    printf("当前停车场车辆：\n");
    for (int i = 0; i <= parking.top; i++) {
        printf("车位%d: %s\n", i + 1, parking.data[i]->license);
    }
}

void showWaiting() {
    if (isWaitingEmpty(&waiting)) {
        printf("便道无等待车辆\n");
        return;
    }
    printf("便道等待车辆：");
    Car *p = waiting.front;
    while (p != NULL) {
        printf("%s ", p->license);
        p = p->next;
    }
    printf("\n");
}

void freeAll() {
    // 释放停车场车辆
    while (!isParkingEmpty(&parking)) {
        Car *car = popParking(&parking);
        free(car);
    }
    // 释放便道车辆
    while (!isWaitingEmpty(&waiting)) {
        Car *car = dequeueWaiting(&waiting);
        free(car);
    }
}

// ========== 主函数 ==========
int main() {
    // 初始化栈和队列
    initParking(&parking);
    initWaiting(&waiting);

    int choice;
    char license[10];

    while (1) {
        printf("\n========== 停车场管理系统 ==========\n");
        printf("1. 车辆到达\n");
        printf("2. 车辆离开\n");
        printf("3. 查看停车场\n");
        printf("4. 查看便道\n");
        printf("0. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入车牌号: ");
                scanf("%s", license);
                arrive(license);
                break;
            case 2:
                printf("请输入车牌号: ");
                scanf("%s", license);
                leave(license);
                break;
            case 3:
                showParking();
                break;
            case 4:
                showWaiting();
                break;
            case 0:
                freeAll();
                printf("系统退出，再见！\n");
                return 0;
            default:
                printf("无效选择！请重新输入。\n");
        }
    }
    return 0;
}