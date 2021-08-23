#include<stdio.h>
typedef struct
{
    int ele[10];
    int front,rear;
}queue;
queue *q;
void insert(queue *q,int x)
{
    if((q->rear==9 && q->front==0)||(q->rear==q->front-1))
    { printf("\nQueue is FULL.\n"); 
    return;   }
    if(q->front==-1)
    q->front=0;
    q->ele[(++q->rear)%10]=x;
    printf("\nData inserted successfully.\n");
}
int delete(queue *q)
{
 
    int data;
    if(q->front==-1)   { printf("\nQueue is empty.\n"); 
    return 0; }
    data=q->ele[q->front];
    if(q->front==q->rear)
    q->front=q->rear=-1;
    else
    q->front=(q->front+1)%10;
    printf("\nData deleted : %d\n",data);    
}
void display(queue *q)
{
    int i;
    if(q->front == -1) 
    { printf("Queue IS EMPTY."); 
    return; }
    for(i=q->front;i!=q->rear+1;(i++)%10)
        printf("%d->",q->ele[i]);
    printf("\n");
}
void main()
{
    int num; 
    int c=1;
    q=(queue *)malloc(sizeof(queue));
    q->front=-1;
    q->rear=-1;
    int choice=0;
    while(c)
    {
    printf("\n1: Add item(Enque)\n2: Remove item(Deque)\n3. Dispaly\nEnter choice 1,2,3:\n");
    scanf("%d",&choice);
    switch(choice)
    {
     
        case 0:
            exit(1);
        break;
        case 1:
            printf("\nEnter an item to insert:");
            scanf("%d",&num);
            insert(q,num);
        break;
        case 2:
            delete(q);
        break;
        case 3:
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


