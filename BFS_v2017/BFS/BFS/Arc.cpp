#include "pch.h"
#include "Arc.h"

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