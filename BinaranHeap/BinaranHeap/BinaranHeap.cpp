#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <list>

using namespace std;

const int minVertexCount = 3;
const int maxVertexCount = 2000;
const int minArcCount = 3;
const int maxArcCount = 200000;

struct MaxPath
{
	int maxPathLength;
	int previousVertex;
};

class Arc
{
public:
	Arc(int vertex, int length);
	int GetVertex() const;
	int GetLength() const;

private:
	int vertex;
	int length;
};

Arc::Arc(int vertex, int length)
	: vertex(vertex)
	, length(length)
{}

int Arc::GetVertex() const
{
	return vertex;
}

int Arc::GetLength() const
{
	return length;
}

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

	if (IsLimitUncorrect(graphVerticesCount, minVertexCount, maxVertexCount) || IsLimitUncorrect(graphArcsCount, minArcCount, maxArcCount))
	{
		cout << "Uncorrect limits." << endl;

		return 0;
	}

	map<int, vector<Arc>> vertexArcs;

	while (getline(input, line))
	{
		input >> arcStart >> arcEnd >> arcLength;
		vector<Arc> acr({ Arc(arcEnd, arcLength) });
		auto const & iter = vertexArcs.find(arcStart);
		if (iter != vertexArcs.end())
		{
			acr.insert(acr.end(), iter->second.begin(), iter->second.end());
		}
		vertexArcs.insert_or_assign(arcStart, acr);
	}

	
	vector<MaxPath> maxPath(graphVerticesCount + 1);
	int* visited = new int[graphVerticesCount + 1];
	visited[startingVertexNumber] = true;

	list<int> queue;
	queue.push_back(startingVertexNumber);

	for (auto & path : maxPath)
	{
		path = MaxPath();
	}

	bool bfs = BFS(graphVerticesCount, startingVertexNumber, endVertexNumber, vertexArcs, maxPath, visited, queue);
	

	if (!bfs)	{		
		cout << "No" << endl;
	}
	else
	{
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

		/*vector<Arc> arcs = (vertexArcs.find(currentVertex) != vertexArcs.end())
			? vertexArcs[currentVertex]
			: vector<Arc>();*/
		vector<Arc> arcs = vertexArcs[currentVertex];
		for (int i = 0; i < arcs.size(); ++i)
		{
			int vertex = arcs[i].GetVertex();
			int length = arcs[i].GetLength();

			if (vertex == 0)
            continue;
			int possibleNewMaxLength = maxPath[currentVertex].maxPathLength + length;
			if (possibleNewMaxLength > maxPath[vertex].maxPathLength)
			{
				maxPath[vertex].maxPathLength = possibleNewMaxLength;
				maxPath[vertex].previousVertex = currentVertex;
				visited[vertex] = false;
			}

			if (!visited[vertex])
			{
				queue.push_back(vertex);
				visited[vertex] = true;
			}
		}
	}

	return true;
	//return BFS(graphVerticesCount, startingVertexNumber, endVertexNumber, vertexArcs, maxPath, visited, queue);
}

void PrintResult(vector<MaxPath> maxPath, int startingVertexNumber, int endVertexNumber) {
	if (startingVertexNumber == endVertexNumber) {
        cout << startingVertexNumber + 1;
    }
	else {
		cout << maxPath[endVertexNumber].maxPathLength << endl;

		vector<int> maxPathVertices;
		while (endVertexNumber != startingVertexNumber)
		{
			maxPathVertices.push_back(endVertexNumber);
			endVertexNumber = maxPath[endVertexNumber].previousVertex;
		}
	
		maxPathVertices.push_back(startingVertexNumber);
		for (int i = maxPathVertices.size() - 1; i >= 0; i--)
		{
			cout << maxPathVertices[i] << " ";
		}
	}
}