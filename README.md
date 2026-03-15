# shuju
上课
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    char bno[20];
    char title[50];
    char sno[20];
    int bStatus;
}Book;
typedef struct node
{
    Book book;
    struct node* next;
}ListNode,*LinkList;
LinkList InitList()
{
    LinkList L;
    L=(ListNode*)malloc(sizeof(ListNode));
    if (L==NULL)
    {printf("分配空间失败，创建单链表不成功！");
    return  NULL;
}
L->next=NULL;
    return L;
}
LinkList CreatListL()
{
    Book book;
    LinkList L=InitList();
    ListNode *s,*r;
    char inputBno[20];
    int continueInput=1;
    r=L;
    while (continueInput){
        scanf("%19s %49s",inputBno,book.title);
        if (strcmp(inputBno,"NULL")==0)
        continueInput=0;
        else
        {
            strcpy(book.bno,inputBno);
            strcpy(book.sno,"NULL");
            book.bStatus=0;
            s=(ListNode*)malloc(sizeof(ListNode));
        if(s==NULL)
    {
        printf("分配空间失败！");
        exit(1);
    }
        s->book=book;
        r->next=s;
        r=s;
     }
  }
  r->next=NULL;
  return L;
}
void PrintList(LinkList L)
{
    ListNode*p;
    p=L->next;
    while(p!=NULL)
    {
      printf("%s\t%-17s\t%s\t%d\n",p->book.bno,p->book.title,p->book.sno,p->book.bStatus);
    p=p->next;  
    }
}
ListNode* LocateList(LinkList L, const char* bname)
{
    ListNode *p = L->next; 
    while (p != NULL)      
    {
        if (strcmp(p->book.title, bname) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}
void BorrowBook(LinkList L)
{
    char sno[20];
    char title[50];
    ListNode *foundNode = NULL;
    
    printf("欢迎借阅图书！请输入您的学号：");
    scanf("%19s", sno);
    
    while (1)
    {
        printf("请输入要借阅的书名：");
        scanf("%49s", title);
        foundNode = LocateList(L, title); 
        
        if (foundNode == NULL)
            printf("图书不存在，请重新输入书名！\n");
        else if (foundNode->book.bStatus == 1)
            printf("图书已被借出，请重新输入书名！\n");
        else
        {
            strcpy(foundNode->book.sno, sno);
            foundNode->book.bStatus = 1;
            printf("借阅成功！\n");
            break;
        }
    }
}
void ReturnBook(LinkList L)
{
    char sno[20];
    char title[50];
    ListNode *foundNode = NULL;
    
    printf("开始归还图书，请输入您的学号：");
    scanf("%19s", sno);
    
    while(1)
    {
        printf("请输入要归还的书名：");
        scanf("%49s", title);
        foundNode = LocateList(L, title); 
        
        if (foundNode == NULL)
            printf("图书不存在，请重新输入书名！\n");
        else if(strcmp(foundNode->book.sno, sno) != 0 || foundNode->book.bStatus != 1)
            printf("您没有借阅过这本书，请检查学号和书名后重新输入！\n");
        else
        {
            strcpy(foundNode->book.sno, "NULL"); 
            foundNode->book.bStatus = 0;         
            printf("图书归还成功！\n");
            break;
        }
    }
}

int main()
{
    LinkList A;
    ListNode *p;
    int ilocate = 1;
    char bname[50];
    
    printf("请依次输入图书的书号和书名(以书号为NULL结束输入):\n");
    A=CreatListL();
    
    printf("\n\t\t\t\t图书信息表\n");
    printf("------------------------------------------------\n");
    printf("书号\t\t书名\t\t借阅人学号\t借阅状态\n");
    printf("------------------------------------------------\n");
    
    PrintList(A); 
    printf("------------------------------------------------\n");
    printf("\n查找图书\n");
    printf("请输入需要查找的图书名称：");
    do
    {
        scanf("%49s", bname);
        p = LocateList(A, bname);
        if (p != NULL)
        {
            printf("您查找的图书信息如下:\n");
            printf("%s\t%s\t%s\t%d\n", p->book.bno, p->book.title, p->book.sno, p->book.bStatus);
            ilocate = 0; 
        }
        else
        {
            printf("您查找的图书不存在! 请重新输入正确的书名: ");
        }
    } while (ilocate);
    printf("\n");
    BorrowBook(A);
    
    printf("\n\t\t\t\t图书信息表\n");
    printf("------------------------------------------------\n");
    printf("书号\t\t书名\t\t借阅人学号\t借阅状态\n");
    printf("------------------------------------------------\n");
    PrintList(A);
    printf("------------------------------------------------\n");
    

    printf("\n");
    ReturnBook(A);
    
    printf("\n\t\t\t\t图书信息表\n");
    printf("------------------------------------------------\n");
    printf("书号\t\t书名\t\t借阅人学号\t借阅状态\n");
    printf("------------------------------------------------\n");
    PrintList(A);
    printf("------------------------------------------------\n");
    
    return 0;
}
