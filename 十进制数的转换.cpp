#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MaxSize 100     // 设定顺序栈的容量，此处设定为100
typedef int DataType;   // 定义顺序栈中数据元素的数据类型
typedef struct
{
    DataType data[MaxSize];    // 定义存储栈元素的数组
    int top;                   // 定义栈顶指针
} Stack;

// 初始化顺序栈
void InitStack(Stack *S)
{
    S->top = -1;
}

// 判断顺序栈是否为空
int EmptyStack(Stack *S)
{
    if (S->top == -1)
        return 1;
    else
        return 0;
}

// 入栈
int Push(Stack *S, DataType x)
{
    if (S->top == MaxSize - 1)
    {   // 判断栈是否已满
        printf("\n 栈已满，无法入栈!");
        return 0;
    }
    S->top++;               // 栈顶指针上移一个位置
    S->data[S->top] = x;    // 将数据元素存入栈顶
    return 1;
}

// 出栈
DataType Pop(Stack *S)
{
    DataType x;
    if (EmptyStack(S))
    {
        printf("\n 栈空，无法出栈!");
        exit(1);
    }
    x = S->data[S->top];    // 记录出栈数据元素的值
    S->top--;               // 栈顶指针下移一个位置
    return x;
}

// 将十进制数转换为非十进制数
void DectoOthers(int n, int b)
{   // 此处b可取2、8、16，表示将十进制转换得到的进制数
    char B[] = "0123456789ABCDEF";
    int x;
    Stack st;
    InitStack(&st);
    while (n)
    {   // 使用“除留取余”法进行数制转换
        Push(&st, n % b);   // 将每次计算的余数入栈
        n = n / b;          // 得到下一次除余计算的n
    }
    while (!EmptyStack(&st))
    {   // 将每次计算的余数出栈（将余数倒序输出）
        x = Pop(&st);
        printf("%c", B[x]);
    }
}

// 主函数
int main()
{
    Stack S;
    int n;
    InitStack(&S);
    printf("请输入一个十进制数: ");
    scanf("%d", &n);
    printf("将十进制数 %d 转换为二进制数的结果为: ", n);
    DectoOthers(n, 2);      // 将十进制数转换为二进制数
    printf("B\n将十进制数 %d 转换为八进制数的结果为: ", n);
    DectoOthers(n, 8);      // 将十进制数转换为八进制数
    printf("O\n将十进制数 %d 转换为十六进制数的结果为: ", n);
    DectoOthers(n, 16);     // 将十进制数转换为十六进制数
    printf("H\n");
    return 0;
}
