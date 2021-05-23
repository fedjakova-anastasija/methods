#include <fstream>
#include <queue>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <list>
#include "Arc.h"

using namespace std;

const int minVertexCount = 3;
const int maxVertexCount = 2000;
const int minArcCount = 3;
const int maxArcCount = 200000;

struct MaxPath
{
	int maxPathLength;
	int prevVertex;
};

bool IsLimitUncorrect(int count, int minCount, int maxCount);
bool BFS(int graphVerticesCount, int startingVertexNumber, int endVertexNumber, map<int, vector<Arc>> vertexArcs, vector<MaxPath>& maxPath, int* visited, list<int> queue);
void PrintResult(vector<MaxPath> results, int startingVertexNumber, int endVertexNumber);

int main()
{
	string inputFileName = "input.txt";
	ifstream input(inputFileName);

	int graphVerticesCount;
	int graphArcsCount;
	int startingVertexNumber;
	int endVertexNumber;

	int arcStart;
	int arcEnd;
	int arcLength;
	string line;
	

	input >> graphVerticesCount >> graphArcsCount >> startingVertexNumber >> endVertexNumber;
	
	vector<MaxPath> maxPath(graphVerticesCount + 1);
	int* visited = new int[graphVerticesCount + 1];
	list<int> queue;
	
	map<int, vector<Arc>> vertexArcs;
	map<int, vector<Arc>>::iterator it;

	if (IsLimitUncorrect(graphVerticesCount, minVertexCount, maxVertexCount) || IsLimitUncorrect(graphArcsCount, minArcCount, maxArcCount))
	{
		cout << "Uncorrect limits." << endl;

		return 0;
	}

	while (getline(input, line))
	{
		input >> arcStart >> arcEnd >> arcLength;
		it = vertexArcs.find(arcStart);

		vector<Arc> arc;
		arc.push_back(Arc(arcEnd, arcLength));
		arc.insert(arc.end(), it->second.begin(), it->second.end());

		vertexArcs[arcStart] = arc;
	}
	
	visited[startingVertexNumber] = true;
	queue.push_back(startingVertexNumber);

	for (int i = 0; i < maxPath.size(); ++i)
		maxPath[i] = MaxPath();	

	if (!BFS(graphVerticesCount, startingVertexNumber, endVertexNumber, vertexArcs, maxPath, visited, queue))	{		
		cout << "No" << endl;
	}
	else
	{
		cout << maxPath[endVertexNumber].maxPathLength << endl;
		PrintResult(maxPath, startingVertexNumber, endVertexNumber);
	}
}

bool IsLimitUncorrect(int count, int minCount, int maxCount) {
	if (count < minCount || count > maxCount) {
		return true;
	}

	return false;
}

bool BFS(int graphVerticesCount, int startingVertexNumber, int endVertexNumber, map<int, vector<Arc>> vertexArcs, vector<MaxPath>& maxPath, int* visited, list<int> queue) {
	if (queue.empty()) {
		return false;
	}

	if (startingVertexNumber == endVertexNumber) {
        return true;
    }

	while (!queue.empty())
	{
		int currentVertex = queue.front();
		queue.pop_front();

		vector<Arc> arcs = vertexArcs[currentVertex];
		for (int i = 0; i < arcs.size(); ++i)
		{
			int vertex = arcs[i].GetVertex();
			int length = arcs[i].GetLength();

			if (vertex == 0)
				continue;

			int testedLength = length + maxPath[currentVertex].maxPathLength;
			if (testedLength < maxPath[vertex].maxPathLength)
				continue;

			maxPath[vertex].maxPathLength = testedLength;
			maxPath[vertex].prevVertex = currentVertex;
			
			queue.push_back(vertex);
			visited[vertex] = true;
		}
	}

	return true;
}

void PrintResult(vector<MaxPath> maxPath, int startingVertexNumber, int endVertexNumber) {
	if (startingVertexNumber == endVertexNumber) {
		cout << startingVertexNumber << " ";
		return;
    }
	else {
		PrintResult(maxPath, startingVertexNumber, maxPath[endVertexNumber].prevVertex);
		cout << endVertexNumber << " ";
	}
}