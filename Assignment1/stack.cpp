#include<iostream> 
#define	MAX	10
using namespace std;
class stack
{
    private:
    int arr[ MAX ], top; 
    public:
    stack( )
    {
        top = -1;
    }
    int push( int	item )
    {
        if( top == MAX - 1 )
        {
            cout << endl << "Stack is full"<<endl; 
            return NULL ;
        }
        top++;
        arr[ top ] = item;
    }
    int pop( )
    {
        if( top == -1 )
        {
            cout << endl << "Stack is empty"<<endl; 
            return NULL;
        }
        int data=arr[ top ]; 
        top--;
        return data;
    }
    void display()
    {
        int i;
        if(top==-1)
        {
            cout<<"Stack Empty"<<endl;
        }
        else
        {
            for(i=0;i<top;i++)
            {
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
    }
};
int main()
{
    char ch='y';
    stack s;
    while(ch)
    {
        int i,x;
        cout<<"1. Push"<<endl;
        cout<<"2. Pop"<<endl;
        cout<<"3. Display"<<endl;
        cout<<"Enter Choice 1,2,3"<<endl;
        cout<<endl;
        cin>>i;
        switch(i)
        {
            case 1: cout<<"Enter data to push"<<endl;
                    cin>>x;
                    s.push(x);
                    break;
            case 2: x=s.pop();
                    cout<<"Poped data is : "<<x<<endl;
                    break;
            case 3: s.display();
                    break;
            default: cout<<"Wrong Choice";
                     break;
            
        }
        cout<<"Want to continue? Enter 'y' to continue and 'n' for exit"<<endl;
        cin>>ch;
        cout<<endl;
    }
    return 0;
}
