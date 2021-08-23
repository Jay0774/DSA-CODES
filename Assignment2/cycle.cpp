#include<iostream>
using namespace std;
class ll{
    struct node
    {
        int data; 
        node *next;
    }*p;
    public:
    ll()
    {
        p=NULL;
    }
    void append(int num)
    {
        if(p==NULL)
        {
            cout<<"Empty List"<<endl;
            return;
        }
        node    * q,* t;
        if( p == NULL )
        {
            p   = new node; 
            p->data = num;
            p->next = NULL;
        }
        else
        {
            q = p;
            while( q->next != NULL ) 
            q = q->next;
            t   = new node; 
            t->data = num;
            t->next = NULL; 
            q->next = t;
        }
    }
    void create( int    num ){
        node    * q;
        q   = new node; 
        q->data = num;
        q->next = p; 
        p   = q;
    }
    void del( int   num ){
        node *t,*q=p;
        if(p==NULL)
        {
            cout<<"Empty List"<<endl;
            return;
        }
        while(q->data!=num)
        {
            t=q;
            q=q->next;
        }
        t->next=q->next;
        delete(q);
    }
    void display(){
        node *q;
        q=p;
        if(p==NULL)
        {
            cout<<"Empty List"<<endl;
            return;
        }
        while(q->next!=NULL)
        {
            cout<<q->data<<"->";
            q=q->next;
        }
        cout<<q->data<<endl;
    }
    void createcycle()
    {
        int d;
        cout<<"Enter data you want to create a cycle:"<<endl;
        cin>>d;
        if(p==NULL)
        {
            cout<<"Empty List"<<endl;
            return;
        }
        node *q=p,*t=p;
        while(t->next!=NULL)
        {
            t=t->next;
        }
        while(q->next!=NULL && q->data!=d)
        {
            q=q->next;
        }
        t->next=q;
    }
    void findcycle()
    {
        int c=0;
        node *q=p,*t=p;
        if(p==NULL)
        {
            cout<<"Empty List"<<endl;
            return;
        }
        while(q->next!=NULL && q!=NULL && t!=NULL)
        {
            q=q->next->next;
            t=t->next;
            if(q==t)
            {
                c=1;
                break;
            }
        }
        if(c==1)
        {
            q=p;
            while(q!=t)
            {
                q=q->next;
                t=t->next;
            }
            cout<<"Cycle Exists at "<<q->data<<endl;
        }
        else if(c==0)
        {
            cout<<"Cycle do not Exists"<<endl;   
        }

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
        cout<<"1. Create"<<endl;
        cout<<"2. Append"<<endl;
        cout<<"3. Delete"<<endl;
        cout<<"4. Create Cycle"<<endl;
        cout<<"5. Find Cycle"<<endl;
        cout<<"6. Dispaly(Not for Cycle)"<<endl;
        cout<<"Enter choice 1,2,3,4,5,6"<<endl;
        cin>>n;
        switch(n)
        {
            case 1: cout<<"Enter Data"<<endl;
                    cin>>d;
                    l.create(d);
                    break;
            case 2: cout<<"Enter Data"<<endl;
                    cin>>d;
                    l.append(d);
                    break;
            case 3: cout<<"Enter Data to delete"<<endl;
                    cin>>d;
                    l.del(d);
                    break;
            case 4: l.createcycle();
                    break;
            case 5: l.findcycle();
                    break;
            case 6: l.display();
                    break;
            default: cout<<"Enter valid Choice"<<endl;
        }
        cout<<"Do you want to continue '1' or '0'"<<endl;
        cin>>ch;
    }
    return 0;
}
