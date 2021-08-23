#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct bst
{
    int data;
    struct bst *l;
    struct bst *r;
};
int ele[10],front=0,rear=-1;
int v;
struct bst *find(struct bst *ro,int d)
{
    if(ro==NULL)
    return NULL;
    if(d<ro->data)
    return find(ro->l,d);
    else if(d>ro->data)
    return find(ro->r,d);
    else
    return ro;
}
struct bst *mini(struct bst *ro)
{
    if(ro==NULL)
    return NULL;
    else if(ro->l==NULL)
    return ro;
    else
    return mini(ro->l);
}
struct bst *maxi(struct bst *ro)
{
    if(ro==NULL)
    return NULL;
    else if(ro->r==NULL)
    return ro;
    else
    return maxi(ro->r);
}
struct bst *insert(struct bst* ,int );
struct bst *insert(struct bst *ro,int d)
{
    if(ro==NULL)
    {
        ro=(struct bst*)malloc(sizeof(struct bst));
        if(ro==NULL)
        {
            printf("Erro");
            return NULL;
        }
        else
        {
            ro->data=d;
            ro->l=ro->r=NULL;
        }
    }
    else
    {
        if(d<=ro->data)
        {
            ro->l=insert(ro->l,d);
        }
        else if(d>ro->data)
        {
            ro->r=insert(ro->r,d);
        }
    }
    return ro;
}
void inorder(struct bst *ro)
{
    if(ro==NULL)
    return;
    inorder(ro->l);
    printf("%d \n",ro->data);
    inorder(ro->r);
}
void display()
{
    int i=0;
    for(i=0;i<=rear;i++)
    {
        printf("%d->",ele[i]);
    }
    printf("\n");
}
void bfs(struct bst *ro)
{
    v = ro->data;
    if ((front <= rear)&&(ro->data == ele[front]))
    {
        if (ro->l != NULL)
            ele[++rear] = ro->l->data;
        if (ro->r != NULL || ro->r  ==  NULL)
            ele[++rear] = ro->r->data;
        front++;
    }
    if (ro->l != NULL)
    {
        bfs(ro->l);
    }
    if (ro->r != NULL)
    {
        bfs(ro->r);
    }
}
int issymmetric(struct bst *a,struct bst *b)
{
    if(a==NULL && b==NULL)
    return 1;
    
    return (a!=NULL && b!=NULL) && issymmetric(a->l,b->r) && issymmetric(a->r,b->l);
}
int symmetric(struct bst *ro)
{
    return issymmetric(ro->l,ro->r);
}
int main()
{
    struct bst *root=NULL;
    int ch=1;
    while(ch)
    {
        int n,d,x;
        printf("1. Insert\n2. Inorder\n3. Check Symmetric\nEnter choice 1,2,3\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    root=insert(root,d);
                    break;
            case 2: inorder(root);
                    break;
            case 3: x=symmetric(root);
                    if(x==1)
                    printf("Symmetric\n");
                    else
                    printf(" NOT Symmetric\n");
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
