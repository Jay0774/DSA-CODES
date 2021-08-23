#include<iostream> 
using namespace std; 
class Queue { 
    public:
    int rear, front; 
    int size; 
    int *circular_queue; 
    Queue(int sz) { 
       front = rear = -1; 
       size = sz; 
       circular_queue = new int[sz]; 
    } 
    void insert(int elem) 
    { 
        if ((front == 0 && rear == size-1) || (rear == (front-1)%(size-1)))  { 
            cout<<"\nQueue is Full"<<endl; 
            return; 
        } 
        else if (front == -1) {     
             front = rear = 0; 
            circular_queue[rear] = elem; 
        } 
       else if (rear == size-1 && front != 0) { 
            rear = 0; 
            circular_queue[rear] = elem; 
        } 
        else {  
            rear++; 
            circular_queue[rear] = elem; 
        } 
    }
    int delete() 
    { 
        if (front == -1)  { 
            cout<<"\nQueue is Empty"<<endl; 
            return -1; 
        } 
        int data = circular_queue[front]; 
        circular_queue[front] = -1; 
        if (front == rear)  { 
            front = -1; 
            rear = -1; 
        } 
        else if (front == size-1) 
            front = 0; 
        else
            front++; 
        return data; 
    } 
    void display() 
    { 
        if (front == -1) { 
            cout<<"\nQueue is Empty"<<endl; 
            return; 
        } 
        cout<<"\nCircular Queue elements: "<<endl; 
        if (rear != front) { 
            for (int i = front; i<= rear; i++) 
                cout<<circular_queue[i]<<" "; 
        } 
        else  { 
            for (int i = front; i< size; i++) 
                cout<<circular_queue[i]<<" "; 
       
            for (int i = 0; i <= rear; i++) 
                cout<<circular_queue[i]<<" "; 
        } 
    } 
}; 
int main() 
{ 
    int n,x;
    cout<<"Enter Size of Queue"<<endl;
    cin>>n;
    Queue q(n); 
    for(int i=0;i<n;i++)
    {
        cout<<"Enter "<<i+1<<" element"<<endl;
        cin>>x;
        q.insert(x);
    }
    cout<<"Printing Queue"<<endl;   
    q.display(); 
    cout<<"Element Dequeued = "<<q.delete()<<endl; 
    cout<<"Element Dequeued = "<<q.delete()<<endl;
    cout<<"Printing Queue"<<endl;   
    q.display();
    return 0; 
}
