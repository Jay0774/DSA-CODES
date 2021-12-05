#include "MaxFlow_MPM_Array.cpp"
#include <iostream>
using namespace std;
int main()
{
	int v, e, i, p, q, w;
	cout << "Enter graph vertices: ";
	cin >> v;
	Graph g(v);
	cout << "\nTaking vertex 0 as source, and " << v - 1 << " as target.\nEnter number of directed edges:";
	cin >> e;
	cout << "\n\nEnter edges as follows: [Source] [Destination] [Capacity]\n";
	for (i = 0; i < e; i++)
	{
		cin >> p >> q >> w;
		g.SetCapacity(p, q, w);
	}
	w = MaxFlow_MPM_Array(g, 0, v - 1);
	cout << "Total flow going out of source = " << w << "\n\n";
	return 0;
}