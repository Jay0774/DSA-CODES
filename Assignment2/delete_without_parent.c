#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
}*head=NULL;
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
void deletenode(struct node *p)
{
    struct node *q,*t;
    q=p;
    while(q->next!=NULL)
    {
        t=q;
        q->data=q->next->data;
        q=q->next;
    }
    t->next=NULL;
    free(q);
}
void delete(int x)
{
    struct node *q;
    if(head->data==x)
    {
        q=head;
    }
    else
    {
        q=head;
        while(q->data!=x)
        {
            q=q->next;
        }
    }
    deletenode(q);
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
        printf("1. Append List\n2. Delete from list\n3. Print\nEnter choice 1,2,3\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    insert(d);
                    break;
            case 2: printf("Enter data(for node pointer):");
                    scanf("%d",&d);
                    delete(d);
                    break;  
            case 3: display();
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
