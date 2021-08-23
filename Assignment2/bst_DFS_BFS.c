#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct bst
{
    int data;
    struct bst *l;
    struct bst *r;
};
typedef struct
{
    int ele[100];
    int front,rear;
}queue;
queue *q;
void insertq(queue *q,int x)
{
    if(q->rear==99)
    { printf("\nQueue is FULL.\n"); 
    return;   }
    q->ele[++q->rear]=x;
}
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
struct bst *insert(struct bst *,int );
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
        if(d<ro->data)
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
void preorder(struct bst *ro)
{
    if(ro==NULL)
    return;
    printf("%d \n",ro->data);
    preorder(ro->l);
    preorder(ro->r);
}
void postorder(struct bst *ro)
{
    if(ro==NULL)
    return;
    postorder(ro->l);
    postorder(ro->r);
    printf("%d \n",ro->data);
}
void bfs(struct bst *ro)
{
    if(ro==NULL)
    {
        return;
    }
    insertq(q,ro->data);
    if(ro->l!=NULL)
    {
        bfs(ro->l);
    }
    if(ro->r!=NULL)
    {
        bfs(ro->r);
    }
}
void display()
{
    for(int i=0;i<=q->rear;i++)
    {
        printf("%d \n",q->ele[i]);
    }
}
int main()
{
    q=(queue*)malloc(sizeof(queue));
    q->front=0;
    q->rear=-1;
    struct bst *root=NULL;
    int ch=1;
    while(ch)
    {
        int n,d;
        printf("1. Insert\n2. Preorder\n3. Inorder\n4. Postorder\n5. BFS\nEnter choice 1,2,3,4,5\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1: printf("Enter Data:");
                    scanf("%d",&d);
                    root=insert(root,d);
                    break;
            case 2: preorder(root);
                    break;
            case 3: inorder(root);
                    break;
            case 4: postorder(root);
                    break;
            case 5: bfs(root);
                    display();
                    break;
            default: printf("Enter Vaild Choice.\n");
        }
        printf("Do you want to continue '1' or '0'?\n");
        scanf("%d",&ch);
    }
}
