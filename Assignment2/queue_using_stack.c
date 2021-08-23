#include<stdio.h>
typedef struct
{
    int ele[100];
    int tos;
}stack;
stack *s1,*s2;
void push(stack *s,int x)
{
    if(s->tos==99)
 
    { printf("\nSTACK is FULL.\n"); 
    return;   }
    s->ele[++s->tos]=x;
}
int pop(stack *s)
{
 
    int data;
    if(s->tos==-1)   { printf("\nSTACK is empty.\n"); 
    return 0; }
    data=s->ele[s->tos];
    s->tos--;
    return data;    
}
void insert(stack *s1,stack *s2,int x)
{
    while(s1->tos!=-1)
    {
        push(s2,pop(s1));
    }
    push(s1,x);
    while(s2->tos!=-1)
    {
        push(s1,pop(s2));
    }
}
int delete(stack *s1,stack *s2)
{
    if(s1->tos==-1)
    {
        printf("Queue is Empty.\n");
        return 0;
    }
    int data=pop(s1);
    printf("Deleted Data is : %d",data);
    return data;
}
void display(stack * s)
{
    int i;
    if(s->tos == -1) 
    { printf("Queue IS EMPTY."); 
    return; }
    for(i=s->tos;i>=1;i--)
        printf("%d->",s->ele[i]);
    printf("%d\n",s->ele[i]);
}
void main()
{
    int num; 
    int c=1;
    int choice=0;
    s1=(stack *)malloc(sizeof(stack));
    s1->tos=-1;
    s2=(stack *)malloc(sizeof(stack));
    s2->tos=-1;
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
            insert(s1,s2,num);
        break;
        case 2:
            delete(s1,s2);
        break;
        case 3:
            display(s1);
        break;
        default:
            printf("\nAn Invalid Choice !!!\n");
        break;
    }
    printf("\nDo you want to continue '1' or '0'\n");
    scanf("%d",&c);
    }
}
