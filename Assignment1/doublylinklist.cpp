#include<iostream>
using namespace std;
class ll{
    struct node
    {
        int	data; 
        node *next;
        node *pre;
    }*p;
    public:
    ll()
    {
        p=NULL;
    }
    void append(int num)
    {
        node	* q,* t;
        if( p == NULL )
        {
            p	= new node; 
            p->data = num;
            p->next = NULL;
            p->pre=NULL;
        }
        else
        {
            q = p;
            while( q->next != NULL ) 
            q = q->next;
            t	= new node; 
            t->data = num;
            t->next = NULL; 
            q->next = t;
            t->pre=q;
        }
    }
    void addatbeg( int	num ){
        node	* q;
        q	= new node; 
        q->data = num;
        q->next = p;
        q->pre=NULL;
        p	= q;
    }
    void del( int	num ){
        node *t,*q=p;
        if(p->data==num)
        {
            q->next=NULL;
            p->next->pre=NULL;
            p=p->next;
            delete(q);
        }
        else
        {
        while(q->data!=num)
        {
            t=q;
            q=q->next;
        }
        if(q->next!=NULL)
        q->next->pre=q->pre;
        else
        q->pre=NULL;
        t->next=q->next;
        delete(q);
        }
    }
    void display( ){
        node *q;
        q=p;
        while(q->next!=NULL)
        {
            cout<<q->data<<"->";
            q=q->next;
        }
        cout<<q->data<<endl;
    } 
    ~ll( )
    {
        delete(p);
    }
};
int main()
{
    ll l;
    int ch=1;
    while(1)
    {
        int n,d;
        cout<<"1. Add at Begenning"<<endl;
        cout<<"2. Append"<<endl;
        cout<<"3. Delete"<<endl;
        cout<<"4. Dispaly"<<endl;
        cout<<"Enter choice 1,2,3,4"<<endl;
        cin>>n;
        switch(n)
        {
            case 1: cout<<"Enter Data"<<endl;
                    cin>>d;
                    l.addatbeg(d);
                    break;
            case 2: cout<<"Enter Data"<<endl;
                    cin>>d;
                    l.append(d);
                    break;
            case 3: cout<<"Enter Data to delete"<<endl;
                    cin>>d;
                    l.del(d);
                    break;
            case 4: l.display();
                    break;
            default: cout<<"Enter valid Choice"<<endl;
        }
        cout<<"Do you want to continue '1' or '0'"<<endl;
        cin>>ch;
    }
    return 0;
}
