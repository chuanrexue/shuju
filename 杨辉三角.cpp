#include <stdio.h>
#include <stdlib.h>
#define MaxSize 30
typedef int DataType;
typedef struct 
{
    DataType data[MaxSize];
    int front,rear;
} Queue;
void InitQueue(Queue *Q)
{
    Q->rear=Q->front=0;
}
int EmptyQueue(Queue *Q)
{
    if(Q->rear==Q->front)
        return 1;
    else
        return 0;
}
int InQueue(Queue *Q, DataType x)
{
    if((Q->rear+1)%MaxSize==Q->front)
    {
        printf("\n队列已满，无法入队！");
        return 0;
    }
    Q->rear=(Q->rear+1)%MaxSize;
    Q->data[Q->rear]=x;
    return 1;
}
int OutQueue(Queue *Q, DataType *x)
{
    if(EmptyQueue(Q))
    {
        printf("\n队列为空，不能出队！");
        return 0;
    }
    Q->front=(Q->front+1)%MaxSize;
    *x=Q->data[Q->front];
    return 1;
}
int GetHeadQueue(Queue *Q,DataType *x)
{
    if(EmptyQueue(Q))
    {
        printf("\n队列为空，无法获取头元素！");
        return 0;
    }
    *x=Q->data[(Q->front+1)%MaxSize];
    return 1;
}
void YangHui(int n)
{
    int i,j,k=0;
    int temp, x;
    Queue Q;
    InitQueue(&Q);
    InQueue(&Q, 1);
    for(i=2;i<=n;i++)
    {
        for ( k=1;k<=30-(i-2)*2;k++)
           printf(" ");
        InQueue(&Q, 1);
        for(j=1;j<=i-2;j++)
        {
            OutQueue(&Q, &temp);
            printf("%d  ", temp);
            GetHeadQueue(&Q, &x);
            temp=temp+x;
            InQueue(&Q, temp);
        }
        OutQueue(&Q, &temp);
        printf("%d\n", temp);
        InQueue(&Q, 1);
    }
    for(k=1;k<=30-(n-1)*2;k++)
       printf(" ");
    for(i=1;i<=n;i++)
    {
        OutQueue(&Q, &temp);
        printf("%d  ", temp);
    }
    printf("\n");
}
int main()
{
    int n;
    printf("请输入杨辉三角的行数：");
    scanf("%d", &n);
    YangHui(n);
}
