#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
}*head=NULL,*head1=NULL;
void insert1(int x)
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
void insert2(int x)
{
    struct node *q;
    struct node *t=(struct node *)malloc(sizeof(struct node));
    t->data=x;
    t->next=NULL;
    if(head1==NULL)
    {
        head1=t;
        return;
    }
    q=head1;
    while(q->next!=NULL)
    {
        q=q->next;
    }
    q->next=t;
}
void delete1(int x)
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
void delete2(int x)
{
    struct node *q,*t;
    if(head1->data==x)
    {
        q=head1;
        head1=head1->next;
        free(q);
    }
    else
    {
    q=head1;
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
    printf("First List:\n");
    struct node *p=head;
    while(p->next!=NULL)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("%d\n",p->data);
    printf("Second List:\n");
    p=head1;
    while(p->next!=NULL)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("%d\n",p->data);
}
void merge()
{
    int x;
    printf("Enter the node of second where first is merged:\n");
    scanf("%d",&x);
    struct node *p=head,*q,*t;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    q=head1;
    while(x--)
    q=q->next;
    p->next=q;
    
    p=head;
    while(p->next!=NULL)
    {
        q=head1;
        while(q->next!=NULL)
        {
            if(p->data==q->data && p==q)
            {
                printf("Lists are merged at: %d\n",p->data);
                break;
            }
            q=q->next;
        }
        p=p->next;
    }
    display();
}
int main()
{
    int ch=1;
    while(ch)
    {
        int n,d;
        printf("1. Append list 1\n2. Append List 2\n3. Delete from list 1\n4. Delete from list 2\n5. Find Merge Point\n6. Display Lists\nEnter choice 1,2,3,4,5,6\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    insert1(d);
                    break;
            case 2: printf("Enter Data:");
                    scanf("%d",&d);
                    insert2(d);
                    break;
            case 3: printf("Enter Data:");
                    scanf("%d",&d);
                    delete1(d);
                    break;
            case 4: printf("Enter Data:");
                    scanf("%d",&d);
                    delete2(d);
                    break;        
            case 5: merge();
                    break;
            case 6: display();
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
}*head=NULL,*head1=NULL;
void insert1(int x)
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
void insert2(int x)
{
    struct node *q;
    struct node *t=(struct node *)malloc(sizeof(struct node));
    t->data=x;
    t->next=NULL;
    if(head1==NULL)
    {
        head1=t;
        return;
    }
    q=head1;
    while(q->next!=NULL)
    {
        q=q->next;
    }
    q->next=t;
}
void delete1(int x)
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
void delete2(int x)
{
    struct node *q,*t;
    if(head1->data==x)
    {
        q=head1;
        head1=head1->next;
        free(q);
    }
    else
    {
    q=head1;
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
    printf("First List:\n");
    struct node *p=head;
    while(p->next!=NULL)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("%d\n",p->data);
    printf("Second List:\n");
    p=head1;
    while(p->next!=NULL)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("%d\n",p->data);
}
void merge()
{
    int x;
    printf("Enter the node of second where first is merged:\n");
    scanf("%d",&x);
    struct node *p=head,*q,*t;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    q=head1;
    while(x--)
    q=q->next;
    p->next=q;
    
    p=head;
    while(p->next!=NULL)
    {
        q=head1;
        while(q->next!=NULL)
        {
            if(p->data==q->data && p==q)
            {
                printf("Lists are merged at: %d\n",p->data);
                break;
            }
            q=q->next;
        }
        p=p->next;
    }
    display();
}
int main()
{
    int ch=1;
    while(ch)
    {
        int n,d;
        printf("1. Append list 1\n2. Append List 2\n3. Delete from list 1\n4. Delete from list 2\n5. Find Merge Point\n6. Display Lists\nEnter choice 1,2,3,4,5,6\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    insert1(d);
                    break;
            case 2: printf("Enter Data:");
                    scanf("%d",&d);
                    insert2(d);
                    break;
            case 3: printf("Enter Data:");
                    scanf("%d",&d);
                    delete1(d);
                    break;
            case 4: printf("Enter Data:");
                    scanf("%d",&d);
                    delete2(d);
                    break;        
            case 5: merge();
                    break;
            case 6: display();
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
