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
}
void insert(int x)
{
    struct node *q;
    struct node *t=(struct node *)malloc(sizeof(struct node));
    t->data=x;
    t->next=NULL;
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
