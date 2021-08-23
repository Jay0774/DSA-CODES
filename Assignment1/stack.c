#include<stdio.h>
typedef struct
{
    int ele[10];
    int tos;
}stack;
stack *s;
void push(stack *s,int x)
{
    if(s->tos==9)
 
    { printf("\nSTACK is FULL.\n"); 
    return;   }
    s->ele[++s->tos]=x;
    printf("\nData inserted successfully.\n");
}
int pop(stack *s)
{
 
    int data;
    if(s->tos==-1)   { printf("\nSTACK is empty.\n"); 
    return 0; }
    data=s->ele[s->tos];
    s->tos--;
    printf("\nData Popped : %d\n",data);    
}
void display(stack *s)
{
    int i;
    if(s->tos == -1) 
    { printf("STACK IS EMPTY."); 
    return; }
    for(i=s->tos;i>=0;i--)
        printf("%d->",s->ele[i]);
    printf("\n");
}
void main()
{
    int num; 
    int c=1;
    s=(stack *)malloc(sizeof(stack));
    s->tos=-1;
    int choice=0;
    while(c)
    {
    printf("\n1: Add item(pop)\n2: Remove item(push)\n3. Dispaly\nEnter choice 1,2,3:\n");
    scanf("%d",&choice);
    switch(choice)
    {
     
        case 0:
            exit(1);
        break;
        case 1:
            printf("\nEnter an item to insert:");
            scanf("%d",&num);
            push(s,num);
        break;
        case 2:
            pop(s);
        break;
        case 3:
            display(s);
        break;
        default:
            printf("\nAn Invalid Choice !!!\n");
        break;
    }
    printf("\nDo you want to continue '1' or '0'\n");
    scanf("%c",&c);
    }
}
