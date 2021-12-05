#include "Graph.cpp"
#include <iostream>
using namespace std;
int MaxFlow_MPM_Array(Graph &OriginalGraph, int source, int target)
{
	int v = OriginalGraph.Vertices, i, j;
	if (v < 2) //Trivial case
		return 0;
	else if (v == 2)
	{ //There is only source and target vertex, and all potential is 0. Cannot use MPM for trivial case
		v = OriginalGraph.FlowAdjMat[source][target] = OriginalGraph.CapacityAdjMat[source][target];
		return v;
	}
	for (i = 0; i < v; i++) //Clear all flow
	{
		for (j = 0; j < v; j++)
		{
			OriginalGraph.FlowAdjMat[i][j] = 0;
		}
	}
	while (true)
	{
		Graph gf = OriginalGraph.ResidualGraph();
		int *levels = gf.LevelGraph(source, target);
		if (levels[target] < 0) //target is unreachable
		{
			delete[] levels;
			break;
		}
		delete[] levels;
		while (true)
		{
		calc:
			int *levels = gf.LevelGraph(source, target);
			for (i = 0; i < v; i++)
			{
				if (levels[i] < 0 || (levels[i] >= levels[target] && target != i))
				{
					gf.ClearAllIncoming(i);
					gf.ClearAllOutgoing(i);
					levels[i] = -1;
				}
			}
			int *Potential = new int[v];
			int MinCapacityValue = INT32_MAX, MinCapacityVertex = -1;
			for (i = 0; i < v; i++)
			{
				if (levels[i] > 0 && i != target)
				{
					Potential[i] = gf.GetPotential(i);
					if (Potential[i] == 0)
					{
						gf.ClearAllIncoming(i);
						gf.ClearAllOutgoing(i);
						delete[] levels;
						goto calc;
					}
					else if (Potential[i] > 0 && Potential[i] < MinCapacityValue)
					{
						MinCapacityValue = Potential[i];
						MinCapacityVertex = i;
					}
				}
				else
					Potential[i] = 0;
			}
			if (MinCapacityVertex == -1)
				break;
			// Push flow from MinCapacityVertex to dest
			Queue bfs;
			int *VertexFlow = new int[v]();
			VertexFlow[MinCapacityVertex] = MinCapacityValue;
			bfs.Push(MinCapacityVertex);
			while (bfs.GetSize() > 0)
			{
				int currentNode = bfs.Top();
				bfs.Pop();
				int flow = VertexFlow[currentNode];
				for (i = 0; i < v && flow > 0; i++)
				{
					if (i != currentNode && levels[i] == levels[currentNode] + 1)
					{
						int allowedflow = gf.CapacityAdjMat[currentNode][i] - gf.FlowAdjMat[currentNode][i];
						if (allowedflow > 0)
						{
							if (allowedflow > flow)
								allowedflow = flow;
							gf.FlowAdjMat[currentNode][i] += allowedflow;
							VertexFlow[i] += allowedflow;
							flow -= allowedflow;
							if (i != target)
								bfs.Push(i);
						}
					}
				}
			}
			// Pull flow from source to MinCapacityVertex
			for (int i = 0; i < v; i++)
				VertexFlow[i] = 0;
			VertexFlow[MinCapacityVertex] = MinCapacityValue;
			bfs.Push(MinCapacityVertex);
			while (bfs.GetSize() > 0)
			{
				int currentNode = bfs.Top();
				bfs.Pop();
				int flow = VertexFlow[currentNode];
				for (i = 0; i < v && flow > 0; i++)
				{
					if (i != currentNode && levels[i] == levels[currentNode] - 1)
					{
						int allowedflow = gf.CapacityAdjMat[i][currentNode] - gf.FlowAdjMat[i][currentNode];
						if (allowedflow > 0)
						{

							if (allowedflow > flow)
								allowedflow = flow;
							gf.FlowAdjMat[i][currentNode] += allowedflow;
							VertexFlow[i] += allowedflow;
							flow -= allowedflow;
							if (i != target)
								bfs.Push(i);
						}
					}
				}
			}
			delete[] VertexFlow;
			delete[] Potential;
		}
		for (i = 0; i < v; i++)
		{
			for (j = 0; j < v; j++)
			{
				if (i != j && gf.FlowAdjMat[i][j] > 0)
				{
					int flow = gf.FlowAdjMat[i][j];
					if (OriginalGraph.EdgeExists(i, j))
						OriginalGraph.FlowAdjMat[i][j] += flow;
					else if (OriginalGraph.EdgeExists(j, i))
						OriginalGraph.FlowAdjMat[i][j] -= flow;
				}
			}
		}
		delete[] levels;
	}
	i = 0;
	for (j = 0; j < v; j++)
		i += OriginalGraph.FlowAdjMat[source][j];
	return i;
}