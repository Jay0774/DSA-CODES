#include<iostream>
using namespace std;
class ll{
    struct node
    {
        int	data; 
        node *next;
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
            p->next = p;
        }
        else
        {
            q = p;
            while( q->next != p ) 
            q = q->next;
            t	= new node; 
            t->data = num;
            t->next = p; 
            q->next = t;
        }
    }
    void addatbeg( int	num ){
        if( p == NULL )
        {
            p	= new node; 
            p->data = num;
            p->next = p;
        }
        else
        {
        node	* q=p,*t;
        while( q->next != p ) 
        q = q->next;
        t	= new node; 
        t->data = num;
        t->next = p;
        p	= t;
        q->next=p;
        }
        
    }
    void del( int	num ){
        node *t,*q=p;
        if(p->data==num)
        {
            t=p;
            while( q->next != p ) 
            q = q->next;
            p=p->next;
            t->next=NULL;
            q->next=p;
            delete(t);
        }
        else
        {
        while(q->data!=num)
        {
            t=q;
            q=q->next;
        }
        t->next=q->next;
        q->next=NULL;
        delete(q);
        }
    }
    void display( ){
        node *q;
        q=p;
        while(q->next!=p)
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
