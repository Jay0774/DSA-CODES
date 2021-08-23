#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
}*head=NULL;
typedef struct
{
    int ele[100];
    int tos;
}stack;
stack *s;
void push(stack *s,int x)
{
    if(s->tos==9)
 
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
    printf("\nData Popped : %d\n",data);    
}
void insert(int x)
{
    struct node *q;
    struct node *t=(struct node *)malloc(sizeof(struct node));
    t->data=x;
    t->next=NULL;
    if(head==NULL)
    {
        head=t;
        return;
    }
    q=head;
    while(q->next!=NULL)
    {
        q=q->next;
    }
    q->next=t;
}
void delete(int x)
{
    struct node *q,*t;
    if(head->data==x)
    {
        q=head;
        head=head->next;
        free(q);
    }
    else
    {
    q=head;
    while(q->data!=x)
    {
        t=q;
        q=q->next;
    }
    t->next=q->next;
    free(q);
    }
}
void display()
{
    struct node *p=head;
    while(p->next!=NULL)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("%d\n",p->data);
}
void reverseREC(struct node* no)
{
    if(no->next == NULL){
        head = no;
        return;
    }
    reverseREC(no->next);
    struct node* rev =no->next;
    rev->next = no;
    no->next = NULL;
}
int size()
{
    int s=0;
    struct node *p=head;
    while(p->next!=NULL)
    {
        s++;
        p=p->next;
    }
    s++;
    return s;
}
void displaystack(stack *s)
{
    printf("Reverse of Linklist is:\n")
    int i;
    if(s->tos == -1) 
    { printf("STACK IS EMPTY."); 
    return; }
    for(i=s->tos;i>=1;i--)
        printf("%d->",s->ele[i]);
    printf("%d\n",s->ele[i]);
}
void reverseSTACK()
{
    s=(stack *)malloc(sizeof(stack));
    s->tos=-1;
    struct node *p=head;
    while(p->next!=NULL)
    {
        push(s,p->data);
        p=p->next;
    }
    push(s,p->data);
    displaystack(s);
}
int main()
{
    int ch=1;
    while(ch)
    {
        int n,d;
        printf("1. Append List\n2. Delete from list\n3. Reverse using Stack\n4. Reverse using Recursion\n5. Print\nEnter choice 1,2,3,4,5\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    insert(d);
                    break;
            case 2: printf("Enter Data:");
                    scanf("%d",&d);
                    delete(d);
                    break;  
            case 3: reverseSTACK();
                    break;      
            case 4: reverseREC(head);
                    break;
            case 5: display();
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
