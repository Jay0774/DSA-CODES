#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
}*head=NULL;
void create(int x)
{
    struct node *t=(struct node *)malloc(sizeof(struct node));
    t->data=x;
    t->next=NULL;
    head=t;
    head->next=head;
}
void insert(int x)
{
    struct node *q;
    struct node *t=(struct node *)malloc(sizeof(struct node));
    q=head;
    while(q->next!=head)
    {
        q=q->next;
    }
    t->data=x;
    t->next=head;
    q->next=t;
}
void delete(int x)
{
    struct node *q,*t;
    if(head->data==x)
    {
        t=head;
        q=head;
        while(q->next!=head)
        {
            q=q->next;
        }
        head=head->next;
        q->next=head;
        free(t);
    }
    else
    {
    q=head;
    while(q->data!=x)
    {
        t=q;
        q=q->next;
    }
    if(q->next==head)
    {
        t->next=head;
        free(q);
    }
    else
    {
    t->next=q->next;
    free(q);
    }
    }
}
void display()
{
    if(head->next==head)
    {
        printf("%d\n",head->data);
    }
    else
    {
    struct node *p=head->next;
    printf("%d->",head->data);
    while(p->next!=head)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("%d\n",p->data);
    }
}
int main()
{
    int ch=1;
    while(ch)
    {
        int n,d;
        printf("1. Create\n2. Append List\n3. Delete from list\n4. Print\nEnter choice 1,2,3,4\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    create(d);
                    break;
            case 2: printf("Enter Data:");
                    scanf("%d",&d);
                    insert(d);
                    break;
            case 3: printf("Enter Data:");
                    scanf("%d",&d);
                    delete(d);
                    break;        
            case 4: display();
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
