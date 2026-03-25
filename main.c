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
    // TODO: 初始化栈，将top设置为-1
}

int isParkingFull(ParkingStack *s) {
    // TODO: 判断栈是否已满，已满返回1，否则返回0
    return 0;  // 占位
}

int isParkingEmpty(ParkingStack *s) {
    // TODO: 判断栈是否为空，为空返回1，否则返回0
    return 0;  // 占位
}

void pushParking(ParkingStack *s, Car *car) {
    // TODO: 将车辆压入栈（停车场）
    // 注意：需要先判断栈是否已满
}

Car* popParking(ParkingStack *s) {
    // TODO: 弹出栈顶车辆并返回
    // 注意：需要先判断栈是否为空
    return NULL;  // 占位
}

Car* topParking(ParkingStack *s) {
    // TODO: 返回栈顶车辆（不弹出）
    // 注意：需要先判断栈是否为空
    return NULL;  // 占位
}

// ========== 队列操作实现 ==========
void initWaiting(WaitQueue *q) {
    // TODO: 初始化队列，front和rear置为NULL，count置为0
}

int isWaitingEmpty(WaitQueue *q) {
    // TODO: 判断队列是否为空，为空返回1，否则返回0
    return 0;  // 占位
}

void enqueueWaiting(WaitQueue *q, Car *car) {
    // TODO: 将车辆入队（便道等待）
    // 注意：
    // 1. 车辆节点已经创建好，直接使用
    // 2. 将car->next设置为NULL
    // 3. 处理空队列和非空队列两种情况
    // 4. 更新count
}

Car* dequeueWaiting(WaitQueue *q) {
    // TODO: 将队首车辆出队并返回
    // 注意：
    // 1. 需要先判断队列是否为空
    // 2. 更新front指针
    // 3. 如果队列变空，rear也要置为NULL
    // 4. 更新count
    return NULL;  // 占位
}

// ========== 辅助函数实现 ==========
int isCarInParking(ParkingStack *s, char *license) {
    // TODO: 遍历停车场栈，检查车牌是否存在
    // 提示：从栈底到栈顶遍历（下标0到top）
    // 存在返回1，否则返回0
    return 0;  // 占位
}

int isCarInWaiting(WaitQueue *q, char *license) {
    // TODO: 遍历便道队列，检查车牌是否存在
    // 提示：从front开始遍历链表
    // 存在返回1，否则返回0
    return 0;  // 占位
}

int findCarInParking(ParkingStack *s, char *license) {
    // TODO: 在停车场栈中查找车辆，返回下标
    // 提示：从栈底到栈顶遍历（下标0到top）
    // 找到返回下标，未找到返回-1
    return -1;  // 占位
}

// ========== 核心功能实现 ==========
void arrive(char *license) {
    // TODO: 实现车辆到达逻辑
    // 1. 检查车辆是否已在停车场或便道（调用isCarInParking和isCarInWaiting）
    //    如果已存在，输出"车辆已在系统中！"并返回
    // 2. 创建新车辆节点 Car *newCar = (Car*)malloc(sizeof(Car));
    //    复制车牌号 strcpy(newCar->license, license);
    //    设置newCar->next = NULL;
    // 3. 如果停车场未满（调用isParkingFull）：
    //    调用pushParking将车辆停入停车场
    //    输出"车辆 %s 已停入停车场（车位%d）\n"
    // 4. 否则：
    //    调用enqueueWaiting将车辆加入便道
    //    输出"停车场已满，车辆 %s 进入便道等待\n"
}

void leave(char *license) {
    // TODO: 实现车辆离开逻辑（这是本次实验的核心难点）
    // 
    // 步骤1：在停车场中查找车辆位置
    // int pos = findCarInParking(&parking, license);
    // if (pos == -1) {
    //     输出"未找到车辆 %s！\n"并返回
    // }
    //
    // 步骤2：暂存目标车辆上方的车辆
    // Car *tempStack[PARKING_SIZE];  // 临时栈数组
    // int tempCount = 0;
    // while (parking.top > pos) {
    //     tempStack[tempCount++] = popParking(&parking);
    // }
    //
    // 步骤3：弹出目标车辆
    // Car *target = popParking(&parking);
    // 输出"车辆 %s 离开，", target->license);
    // free(target);  // 释放内存
    //
    // 步骤4：将暂存车辆重新入栈（注意顺序：后出栈的先入栈）
    // for (int i = tempCount - 1; i >= 0; i--) {
    //     pushParking(&parking, tempStack[i]);
    // }
    // 输出"其后车辆重新停入\n"
    //
    // 步骤5：如果便道非空，将队首车辆移入停车场
    // if (!isWaitingEmpty(&waiting)) {
    //     Car *waitCar = dequeueWaiting(&waiting);
    //     pushParking(&parking, waitCar);
    //    输出"便道车辆 %s 进入停车场\n", waitCar->license);
    // }
}

void showParking() {
    // TODO: 显示停车场状态
    // 如果停车场为空，输出"停车场为空"
    // 否则，按从入口到出口的顺序显示（即从栈底到栈顶）
    // 格式：车位1: 车牌号
    //       车位2: 车牌号
    //       ...
}

void showWaiting() {
    // TODO: 显示便道状态
    // 如果便道为空，输出"便道无等待车辆"
    // 否则，按排队顺序显示（从队头到队尾）
    // 格式：便道等待车辆：A001 A002 A003
}

void freeAll() {
    // TODO: 释放所有动态分配的内存
    // 1. 释放停车场中的所有车辆节点
    //    while (!isParkingEmpty(&parking)) {
    //        Car *car = popParking(&parking);
    //        free(car);
    //    }
    // 2. 释放便道中的所有车辆节点
    //    while (!isWaitingEmpty(&waiting)) {
    //        Car *car = dequeueWaiting(&waiting);
    //        free(car);
    //    }
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