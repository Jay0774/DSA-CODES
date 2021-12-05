#include "Queue.cpp"
class Graph
{
private:
	int Vertices;
	int **CapacityAdjMat;
	int **FlowAdjMat;

	Graph &ResidualGraph()
	{
		Graph *Gf = new Graph(Vertices);
		int i, j;
		for (i = 0; i < Vertices; i++)
		{
			for (j = 0; j < Vertices; j++)
			{
				if (i == j)
					continue;
				else if (EdgeExists(i, j))
					Gf->SetCapacity(i, j, CapacityAdjMat[i][j] - FlowAdjMat[i][j]);
				else
					Gf->SetCapacity(i, j, FlowAdjMat[j][i]);
			}
		}
		return *Gf;
	}
	int *LevelGraph(int source, int target)
	{
		int *Level = new int[Vertices], i;
		int *Preds = new int[Vertices];
		for (i = 0; i < Vertices; i++)
			Level[i] = Preds[i] = -1; //All are unvisited
		Queue search;
		search.Push(source);
		Level[source] = 0; //Source is at level 0
		while (search.GetSize() > 0)
		{
			int currentNode = search.Top();
			int currentLevel = Level[currentNode];
			search.Pop();
			for (i = 0; i < Vertices; i++)
			{ //For all neigbours of current node
				if (i == currentNode)
					continue;
				else if (EdgeExists(currentNode, i) && Level[i] < 0) //Unvisited node
				{
					Level[i] = currentLevel + 1;
					if (i != target)
						search.Push(i);
				}
			}
		}
		for(i=0;i<Vertices;i++)
		{
			for(int j=0;j<Vertices;j++)
			{
				if(Level[i]+1!=Level[j])
				{
					CapacityAdjMat[i][j]=0;
				}
			}
		}
		return Level;
	}

public:
	Graph(int vertices)
	{
		Vertices = vertices;
		CapacityAdjMat = new int *[Vertices];
		FlowAdjMat = new int *[Vertices];
		for (int i = 0; i < Vertices; i++)
		{
			CapacityAdjMat[i] = new int[Vertices]();
			FlowAdjMat[i] = new int[Vertices]();
		}
	}
	~Graph()
	{
		for (int i = 0; i < Vertices; i++)
		{
			delete[] CapacityAdjMat[i];
		}
		delete[] CapacityAdjMat;
		if (FlowAdjMat != nullptr)
		{

			for (int i = 0; i < Vertices; i++)
			{
				delete[] FlowAdjMat[i];
			}
			delete[] FlowAdjMat;
		}
	}
	void SetFlow(int source, int dest, int value)
	{
		FlowAdjMat[source][dest] = value;
	}
	void SetCapacity(int source, int dest, int value)
	{
		CapacityAdjMat[source][dest] = value;
	}
	int GetFlow(int source, int dest)
	{
		return FlowAdjMat[source][dest];
	}
	int GetCapacity(int source, int dest)
	{
		return CapacityAdjMat[source][dest];
	}
	bool EdgeExists(int source, int dest)
	{
		return CapacityAdjMat[source][dest] > 0;
	}
	void ClearAllIncoming(int vertex)
	{
		for (int i = 0; i < Vertices; i++)
		{
			CapacityAdjMat[i][vertex] = 0;
		}
	}
	void ClearAllOutgoing(int vertex)
	{
		for (int i = 0; i < Vertices; i++)
		{
			CapacityAdjMat[vertex][i] = 0;
		}
	}
	int GetPotential(int vertex)
	{
		int outgoing = 0, incoming = 0, v;
		for (int i = 0; i < Vertices; i++)
		{
			v = CapacityAdjMat[i][vertex] - FlowAdjMat[i][vertex];
			if (v > 0)
				incoming += v;
			v = CapacityAdjMat[vertex][i] - FlowAdjMat[vertex][i];
			if (v > 0)
				outgoing += v;
		}
		return incoming < outgoing ? incoming : outgoing;
	}
	friend int MaxFlow_MPM_Array(Graph &g, int source, int target);
	friend int MaxFlow_MPM_Heap(Graph &g, int source, int target);
};
