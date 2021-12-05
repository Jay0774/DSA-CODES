#include "tests.cpp"

void QueueTestsBoilerplate(int id, int *p, int size)
{
	Queue q;
	for (int i = 0; i < size; i++)
		q.Push(p[i]);
	RunTest(id, "Queue-Push-Test", GetIntArrayString(p, size), GetQueueString(q));
}

void QueuePushTests()
{
	cout << "Starting Queue push testing\n";
	int x[] = {12, 3, 36, 27, 46, 254, 5825, 37, 234, 6, 483, 3, 4, 35, 24, 48, 24, 58, 435, 6, 5, 36, 65, 235, 57, 345, 68, 233, 57, 45, 34, 57};
	QueueTestsBoilerplate(1, x, 32);
	int y[] = {36, 7, 472, 3, 48, 44, 854, 7, 48, 36, 6234, 77, 57, 437, 36, 45, 788, 56};
	QueueTestsBoilerplate(2, y, 18);
	int z[] = {637, 2, 5, 68, 345, 345, 58, 4653, 47, 345, 5, 8, 456, 34, 57, 453};
	QueueTestsBoilerplate(3, z, 16);
}

void QueuePopTests()
{
	cout << "Starting Queue Pop testing\n";
	int w[] = {23, 63, 37, 34, 84, 25, 47};
	int size = sizeof(w) / sizeof(int);
	Queue q;
	for (int i = 0; i < size; i++)
	{
		q.Push(w[i]);
	}
	for (int i = 0; i < size; i++)
	{
		int z = q.Top();
		string exp = to_string(w[i]) + " " + to_string(true);
		string act = to_string(z) + " " + to_string(q.Pop());
		RunTest(i, "Queue Pop Test", exp, act);
	}
	string exp = "0 " + to_string(false);
	string act = to_string(q.Top()) + " " + to_string(q.Pop());
	RunTest(size, "Queue Pop Test", exp, act);
}
void HeapTests()
{
	FibonacciHeap heap;
	int x[] = {87, 3, 46, 57, 35, 57, 95, 2, 94, 72, 59, 37, 74, 37, 39, 25, 4, 58, 23};
	int size = sizeof(x) / sizeof(int);
	for (int i = 0; i < size; i++)
	{
		heap.Insert(x[i]);
	}
	Queue q;
	while (heap.GetSize() > 0)
	{
		q.Push(heap.GetTop());
		heap.DeleteMin();
	}
	int sorted[] = {2, 3, 4, 23, 25, 35, 37, 37, 39, 46, 57, 57, 58, 59, 72, 74, 87, 94, 95};
	RunTest(1, "Heap Test", GetIntArrayString(sorted, size), GetQueueString(q));
}

void MPM_Test0()
{
	int v = 2, e = 1, i, w;
	Graph g(v);
	g.SetCapacity(0, 1, 5);
	w = MaxFlow_MPM_Array(g, 0, 1);
	RunTest(3, "MPM Test", "5", to_string(w));
}

void MPM_Test1()
{
	int v = 4, e = 3, i, w;
	Graph g(v);
	g.SetCapacity(0, 1, 4);
	g.SetCapacity(1, 2, 5);
	g.SetCapacity(2, 3, 10);
	w = MaxFlow_MPM_Array(g, 0, 3);
	RunTest(3, "MPM Test", "4", to_string(w));
}

void MPM_Test2()
{
	int v = 5, e = 5, i, w;
	Graph g(v);
	g.SetCapacity(0, 1, 10);
	g.SetCapacity(1, 2, 11);
	g.SetCapacity(2, 4, 12);
	g.SetCapacity(1, 3, 12);
	g.SetCapacity(3, 4, 11);
	w = MaxFlow_MPM_Array(g, 0, 4);
	RunTest(1, "First Array Test", "10", to_string(w));
}
void testcase_1_Array_Abhijit()
{
	int w, i;
	Graph g(5);
	g.SetCapacity(0, 1, 20);
	g.SetCapacity(0, 2, 15);
	g.SetCapacity(1, 2, 18);
	g.SetCapacity(2, 3, 10);
	g.SetCapacity(1, 4, 8);
	g.SetCapacity(2, 4, 3);
	g.SetCapacity(3, 4, 12);
	w = MaxFlow_MPM_Array(g, 0, 4);
	RunTest(1, "Initial Test", "21", to_string(w));
}
void testcase_1_Heap_Abhijit()
{
	int w, i;
	Graph g(5);
	g.SetCapacity(0, 1, 20);
	g.SetCapacity(0, 2, 15);
	g.SetCapacity(1, 2, 18);
	g.SetCapacity(2, 3, 10);
	g.SetCapacity(1, 4, 8);
	g.SetCapacity(2, 4, 3);
	g.SetCapacity(3, 4, 12);
	w = MaxFlow_MPM_Heap(g, 0, 4);
	RunTest(2, "First Heap Test", "21", to_string(w));
}

void testcase_2_Array_Abhijit()
{
	int w, i;
	Graph g(6);
	g.SetCapacity(0, 1, 7);
	g.SetCapacity(0, 2, 4);
	g.SetCapacity(2, 1, 3);
	g.SetCapacity(1, 3, 5);
	g.SetCapacity(1, 4, 3);
	g.SetCapacity(2, 4, 2);
	g.SetCapacity(4, 3, 3);
	g.SetCapacity(4, 5, 5);
	g.SetCapacity(3, 5, 8);
	w = MaxFlow_MPM_Array(g, 0, 5);
	RunTest(3, "Second Array Test", "10", to_string(w));
}

void testcase_2_Heap_Abhijit()
{
	int w, i;
	Graph g(6);
	g.SetCapacity(0, 1, 7);
	g.SetCapacity(0, 2, 4);
	g.SetCapacity(2, 1, 3);
	g.SetCapacity(1, 3, 5);
	g.SetCapacity(1, 4, 3);
	g.SetCapacity(2, 4, 2);
	g.SetCapacity(4, 3, 3);
	g.SetCapacity(4, 5, 5);
	g.SetCapacity(3, 5, 8);
	w = MaxFlow_MPM_Heap(g, 0, 5);
	RunTest(4, "Second Heap Test", "10", to_string(w));
}

void testcase_3_Array_Abhijit()
{
	int w, i;
	Graph g(6);
	g.SetCapacity(0, 1, 100);
	g.SetCapacity(0, 2, 100);
	g.SetCapacity(1, 2, 1);
	g.SetCapacity(1, 3, 100);
	g.SetCapacity(1, 4, 1);
	g.SetCapacity(2, 4, 100);
	g.SetCapacity(2, 3, 1);
	g.SetCapacity(3, 4, 1);
	g.SetCapacity(3, 5, 100);
	g.SetCapacity(4, 5, 100);
	w = MaxFlow_MPM_Array(g, 0, 5);
	RunTest(5, "Third Array Test", "200", to_string(w));
}

void testcase_3_Heap_Abhijit()
{
	int w, i;
	Graph g(6);
	g.SetCapacity(0, 1, 100);
	g.SetCapacity(0, 2, 100);
	g.SetCapacity(1, 2, 1);
	g.SetCapacity(1, 3, 100);
	g.SetCapacity(1, 4, 1);
	g.SetCapacity(2, 4, 100);
	g.SetCapacity(2, 3, 1);
	g.SetCapacity(3, 4, 1);
	g.SetCapacity(3, 5, 100);
	g.SetCapacity(4, 5, 100);
	w = MaxFlow_MPM_Heap(g, 0, 5);
	RunTest(6, "Third Heap Test", "200", to_string(w));
}

void MPM_Test3()
{
	int v = 6, e = 8, i, w;
	Graph g(v);
	g.SetCapacity(0, 1, 5);
	g.SetCapacity(1, 5, 1);
	g.SetCapacity(0, 2, 4);
	g.SetCapacity(2, 5, 1);
	g.SetCapacity(0, 3, 10);
	g.SetCapacity(3, 5, 1);
	g.SetCapacity(0, 4, 12);
	g.SetCapacity(4, 5, 1);
	w = MaxFlow_MPM_Array(g, 0, 5);
	RunTest(3, "MPM Test", "4", to_string(w));
}

void MPM_Test4()
{
    int v=5,e=5,i,w;
    Graph g(v);
    g.SetCapacity(0,1,10);
    g.SetCapacity(1,2,50);
    g.SetCapacity(2,4,4);
    g.SetCapacity(0,3,15);
    g.SetCapacity(3,4,9);
    w = MaxFlow_MPM_Array(g, 0, 4);
    RunTest(4,"Test 4","13",to_string(w));
}

int main()
{
	QueuePushTests();
	QueuePopTests();
	MPM_Test0();
	MPM_Test1();
	MPM_Test2();
	MPM_Test3();
	MPM_Test4();
	testcase_1_Array_Abhijit();
	testcase_2_Array_Abhijit();
	testcase_3_Array_Abhijit();
	testcase_1_Heap_Abhijit();
	testcase_2_Heap_Abhijit();
	testcase_3_Heap_Abhijit();
	return 0;
}
