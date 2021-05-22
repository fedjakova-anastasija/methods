#pragma once

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