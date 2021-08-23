#include<iostream>
using namespace std;
struct dataele
        {                  
            int data,priority;
        }de[5];
    class priorityqueue
    {
        
        int front,rear;
        public:
        priorityqueue()
        {
            front=rear=-1;
        }
    void enque(dataele de1)
    {
                if(rear==4)
                   cout<<"\nPriority Queue is Full";
                else
                {
                   rear++;
                   de[rear]=de1;
                   if(front==-1)
                          front=0;
                   dataele temp;
                   for(int i=front;i<=rear;i++)
                         for(int j=i+1;j<=rear;j++)
                         {
                                 if(de[i].priority > de[j].priority)
                                 {
                                        temp=de[i];
                                        de[i]=de[j];
                                        de[j]=temp;
                                 }
                         }
                }
        }
        dataele deeque()
        {
                dataele de1;
                if(front==-1)
                   cout<<"\nPriority Queue is Empty";
                else
                {
                   de1=de[front];
                   if(front==rear)
                          front=rear=-1;
                   else
                          front++;
                }
                return de1;
        }
        void display()
        {
                 if(front==-1)
                         cout<<"\nPriority Queue is Empty";
                 else
                 {
                        for(int i=front;i<=rear;i++)
                        {
                                cout<<de[i].data<<"->";
                        }
                        cout<<endl;
                 }
        }
    };
    
        int main()
        {
          priorityqueue p;
          dataele de1;
          char o='y';
          while(o=='y')
          {
                int ch;
                cout<<"\n1.Insertion\n2.deletion\n3.display\n4.Exit\n";
                cout<<"\nEnter your Choice 1,2,3,4 ";
                cin>>ch;
                switch(ch)
                {
                   case 1 :  cout<<"Enter data to insert"<<endl;
                                         cin>>de1.data;
                                         cout<<"Enter priority"<<endl;
                                         cin>>de1.priority;
                                         p.enque(de1);
                                         break;

                   case 2 :  de1=p.deeque();
                                         cout<<"Value = "<<de1.data<<endl;
                                         cout<<"priority = "<<de1.priority<<endl;
                                         break;

                   case 3 :  p.display();
                                         break;
                  }
                  cout<<"\nDo You Want to Continue 'y' or 'n'";
                  cin>>o;
                }
        return 0;
          }