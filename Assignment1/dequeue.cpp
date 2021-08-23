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
            for(int i=0;i<MAX;i++)
            arr[i]=0;
        }
        int addqfront(int item)
        {
            if( (rear == MAX - 1 || front==0 ) && rear==front-1 )
            {
                cout << endl << "Queue is full"<<endl; 
                return 0;
            }
            if( front == -1 )
            front =rear= 0;
            else if(front==0)
            front=MAX-1;
            else
            front--;
            arr[front] = item;
        }
        int delqfront( )
        {
            int data;
            if( front == -1 )
            {
                cout << endl << "Queue is empty"<<endl;
                return 0;
            }
            data = arr[ front ]; 
            arr[front]=0;
            if( front == rear )
            front = rear = -1; 
            else
            front++;
            cout<<"Deleted data is : "<<data<<endl;
        }
        int addqrear(int item)
        {
            if( (rear == MAX - 1 || front==0 ) && rear==front-1 )
            {
                cout << endl << "Queue is full"<<endl; 
                return 0;
            }
            if( front == -1 )
            front = rear = 0;
            else if(rear==MAX-1)
            rear=0;
            else
            rear++;
            arr[rear]=item;
        }
        int delqrear( )
        {
            int data;
            if( front == -1 )
            {
                cout << endl << "Queue is empty"<<endl;
                return 0;
            }
            data = arr[ rear ];
            arr[rear]=0;
            if( front == rear )
            front = rear = -1; 
            else
            rear--;
            cout<<"Deleted data is : "<<data<<endl;
        }
        int display()
        {
            for(int i=0;i<=MAX;i++)
            {
                cout<<arr[i]<<"->";
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
        cout<<"1. Insert in front Queue"<<endl;
        cout<<"2. Delete From front Queue"<<endl;
        cout<<"3. Insert in rear Queue"<<endl;
        cout<<"4. Delete From rear Queue"<<endl;
        cout<<"5. Display"<<endl;
        cout<<"Enter Choice 1,2,3"<<endl;
        cout<<endl;
        cin>>i;
        switch(i)
        {
            case 1: cout<<"Enter data to Insert"<<endl;
                    cin>>x;
                    q.addqfront(x);
                    break;
            case 2: q.delqfront();
                    break;
            case 3: cout<<"Enter data to Insert"<<endl;
                    cin>>x;
                    q.addqrear(x);
                    break;
            case 4: q.delqrear();
                    break;
            case 5: q.display();
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
