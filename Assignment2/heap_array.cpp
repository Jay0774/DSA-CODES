#include <iostream> 
using namespace std;
void heapify(int a[],int n,int i)
{
    int lar = i; 
    int leftc = 2 * i + 1; 
    int rightc = 2 * i + 2;
    if (leftc < n && a[leftc] > a[lar])
        lar = leftc;
    if (rightc < n && a[rightc] > a[lar])
        lar = rightc;
    if (lar != i) {
        swap(a[i], a[lar]);
        heapify(a, n, lar);
    }
}
void build(int a[], int n)
{
    int s = (n/2) - 1;
    for (int i = s; i >= 0; i--) {
        heapify(a, n, i);
    }
}
void print(int a[], int n)
{
    cout << "Array representation of the creted Heap is:\n";
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << "\n";
}
int main()
{
    int n;
    cout<<"Enter Number of elements of heap:"<<endl;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Enter "<<i+1<<" element"<<endl;
        cin>>a[i];
    }
    build(a, n);
    print(a, n);
    return 0;
}