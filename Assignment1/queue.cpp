#include<iostream> 
#define	MAX	10
using namespace std;
class queue
{
    private:
        int arr[ MAX ]; 
        int front,rear;
    public:
        queue( )
        {
            front=-1;
            rear=-1;
        }
        int addq(int item)
        {
            if( rear == MAX - 1 )
            {
                cout << endl << "Queue is full"<<endl; 
                return NULL;
            }
            rear++;
            arr[ rear ] = item; 
            if( front == -1 )
            front = 0;
        }
        int delq( )
        {
            int data;
            if( front == -1 )
            {
                cout << endl << "Queue is empty"<<endl;
                return NULL;
            }
            data = arr[ front ]; 
            if( front == rear )
            front = rear = -1; 
            else
            front++;
            cout<<"Deleted data is : "<<data<<endl;
        }
        int display()
        {
            int i;
            if(front == -1)
            {
                cout<<"Empty Queue"<<endl;
            }
            else
            {
                for(i=front;i<=rear;i++)
                {
                    cout<<arr[i]<<" ";
                }   
            }
            cout<<endl;
        }

};
int main()
{
    char ch='y';
    queue q;
    while(ch)
    {
        int i,x;
        cout<<"1. Insert in Queue"<<endl;
        cout<<"2. Delete From Queue"<<endl;
        cout<<"Enter Choice 1,2,3"<<endl;
        cout<<endl;
        cin>>i;
        switch(i)
        {
            case 1: cout<<"Enter data to Insert"<<endl;
                    cin>>x;
                    q.addq(x);
                    break;
            case 2: q.delq();
                    Break;
case 3: q.display();
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
