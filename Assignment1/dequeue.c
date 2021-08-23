#include<stdio.h>
typedef struct
{
    int ele[10];
    int front,rear;
}dqueue;
dqueue *q;
void addfront(dqueue *q,int x)
{
    int k,i;
    if(q->rear==9 && q->front==0)
    { printf("\nQueue is FULL.\n"); 
    return;   }
    if(q->front==-1)
    {
        q->front=q->rear=0;
        q->ele[q->front]=x;
        return;
    }
    if(q->rear!=9)
    {
        for(i=q->rear+1;i!=q->front;i--)
        q->ele[i]=q->ele[i-1];
        q->ele[i]=x;
        q->rear++;
    }
    else
    {
        q->front--;
        q->ele[q->front]=x;
    }
    printf("\nData inserted at front successfully.\n");
}
void addrear(dqueue *q,int x)
{
    int k,i;
    if(q->rear==9 && q->front==0)
    { printf("\nQueue is FULL.\n"); 
    return;   }
    if(q->front==-1)
    {
        q->front=q->rear=0;
        q->ele[q->rear]=x;
        return;
    }
    q->rear++;
    q->ele[q->rear]=x;
    printf("\nData inserted at rear successfully.\n");
}
int deletefront(dqueue *q)
{
 
    int data;
    if(q->front==-1)   { printf("\nQueue is empty.\n"); 
    return 0; }
    data=q->ele[q->front];
    q->ele[q->front]=0;
    if(q->front==q->rear)
    q->front=q->rear=-1;
    else
    q->front++;
    printf("\nData deleted from front : %d\n",data);    
}
int deleterear(dqueue *q)
{
 
    int data;
    if(q->front==-1)   { printf("\nQueue is empty.\n"); 
    return 0; }
    data=q->ele[q->rear];
    q->ele[q->rear]=0;
    q->rear--;
    if(q->rear==-1)
    q->front=-1;
    printf("\nData deleted from rear : %d\n",data);    
}
void display(dqueue *q)
{
    int i;
    for(i=0;i<=9;i++)
        printf("%d->",q->ele[i]);
    printf("\n");
}
void main()
{
    int num; 
    int c=1;
    q=(dqueue *)malloc(sizeof(dqueue));
    q->front=-1;
    q->rear=-1;
    for(int i=0;i<10;i++)
    {
        q->ele[i]=0;
    }
    int choice=0;
    while(c)
    {
    printf("\n1: Add item(Enque) at front\n2: Remove item(Deque) from front\n3: Add item(Enque) at reart\n4: Remove item(Deque) from rear\n5. Dispaly\nEnter choice 1,2,3,4,5:\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            printf("\nEnter an item to insert:");
            scanf("%d",&num);
            addfront(q,num);
        break;
        case 2:
            deletefront(q);
        break;
        case 3:
            printf("\nEnter an item to insert:");
            scanf("%d",&num);
            addrear(q,num);
        break;
        case 4:
            deleterear(q);
        break;
        case 5:
            display(q);
        break;
        default:
            printf("\nAn Invalid Choice !!!\n");
        break;
    }
    printf("\nDo you want to continue '1' or '0'\n");
    scanf("%d",&c);
    }
}
