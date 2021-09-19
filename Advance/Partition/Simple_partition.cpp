#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void display(int name[],int n)
{
    int i,j,m[n]={0};
    for(i=0;i<n;i++)
    {
        if(m[name[i]-1]==0)
        {
            cout<<"Set "<<name[i]<<" has "<<i+1;
            for(j=i+1;j<n;j++)
            {
                if(name[j]==name[i])
                cout<<" "<<j+1;
            }
            cout<<endl;
            m[name[i]-1]++;
        }
    }
}
int main()
{
    int n,i,ch=1;
    cout<<"Enter number of elements:"<<endl;
    cin>>n;
    int name[n];
    for(i=0;i<n;i++)
    {
        name[i]=i+1;
    }
    while(ch)
    {
        int x,a,b,i,j;
        cout<<"1. Union"<<endl<<"2. Find"<<endl<<"3. Display"<<endl<<"Enter your choice"<<endl;
        cin>>x;
        switch(x)
        {
            case 1: cout<<"Enter a,b"<<endl;
                    cin>>a>>b;
                    if(a<b)
                    {
                        for(i=0;i<n;i++)
                        {
                            if(name[i]==b)
                            name[i]=a;
                        }
                    }
                    else
                    {
                        for(i=0;i<n;i++)
                        {
                            if(name[i]==a)
                            name[i]=b;
                        }
                    }
                    break;
            case 2: cout<<"Enter element to find"<<endl;
                    cin>>a;
                    for(i=0;i<n;i++)
                    {
                        if(i+1==a)
                        cout<<name[i]<<endl;
                    }
                    break;
            case 3: display(name,n);
                    break; 
            default: cout<<"Enter valid choice..."<<endl;
                     break;
        }
        cout<<"Do you want to continue?. Enter 1 or 0:";
        cin>>ch;
    }
    display(name,n);
}