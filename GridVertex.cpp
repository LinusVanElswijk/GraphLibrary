#include "GridVertex.hpp"
#include <iostream>

namespace graphs
{
	GridVertex::GridVertex(Vertex &vertex, const UInt &x, const UInt &y)
	:Vertex(vertex),
	 x(x),
	 y(y)
	{
	}

	GridVertex::GridVertex(GridVertex& gridVertex)
	:Vertex(gridVertex),
	 x(gridVertex.x),
	 y(gridVertex.y)
	{
	}

	GridGraph& GridVertex::getGraph()
	{
		Graph& graph = Vertex::getGraph();
		return static_cast< GridGraph& >(graph);
	}

	const GridGraph& GridVertex::getGraph() const
	{
		const Graph& graph = Vertex::getGraph();
		return static_cast< const GridGraph& >(graph);
	}

	unsigned int GridVertex::getX() const
	{
		//return getGraph().indexToX(this->getIndex());
		return x;
	}

	unsigned int GridVertex::getY() const
	{
		//return getGraph().indexToY(this->getIndex());
		return y;
	}
}//graphs
