#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
}*head1=NULL,*head2=NULL;
void insert(struct node *head,int x)
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
void delete(struct node *head,int x)
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
        printf("1. Append list 1\n2. Append List 2\n3. Delete from list 1\n4. Delete from list 2\n5. Print list 1\n6. Print list 2\nEnter choice 1,2,3,4,5,6\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    insert(head1,d);
                    break;
            case 2: printf("Enter Data:");
                    scanf("%d",&d);
                    insert(head2,d);
                    break;
            case 3: printf("Enter Data:");
                    scanf("%d",&d);
                    delete(head1,d);
                    break;
            case 4: printf("Enter Data:");
                    scanf("%d",&d);
                    delete(head2,d);
                    break;
            case 5: display(head1);
                    break;        
            case 6: display(head2);
                    break;
            case 7: merge(head1,head2);
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
