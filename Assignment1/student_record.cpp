#include <iostream>
using namespace std;
class student
{
    private:
    int id;
    string name;
    int age;
    public:
    void set()
    {
        cout<<"Enter ID of student:"<<endl;
        cin>>id;
        cout<<"Enter Name of student:"<<endl;
        cin>>name;
        cout<<"Enter Age of student:"<<endl;
        cin>>age;
    }
    void print()
    {
        cout<<"Id : "<<id<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }
};
int main() {
    int n,i;
    cout<<"Enter Number of Students:"<<endl;
    cin>>n;
	student s[n];
	for(i=0;i<n;i++)
	s.set();
	for(i=0;i<n;i++)
	s.print();
	return 0;
}
