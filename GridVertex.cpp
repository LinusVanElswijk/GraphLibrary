#include "GridVertex.hpp"
#include <iostream>

namespace graphs
{
	template<typename precision>
	GridVertex<precision>::GridVertex(Graph<precision>& graph, const unsigned int& x, const unsigned int& y)
	:Vertex<precision>(graph),
	 x(x),
	 y(y)
	{
	}

	template<typename precision>
	GridGraph<precision>& GridVertex<precision>::getGraph()
	{
		Graph<precision>& graph = Vertex<precision>::getGraph();
		return static_cast<GridGraph<precision>& >(graph);
	}

	template<typename precision>
	const GridGraph<precision>& GridVertex<precision>::getGraph() const
	{
		const Graph<precision>& graph = Vertex<precision>::getGraph();
		return static_cast<const GridGraph<precision>& >(graph);
	}

	template<typename precision>
	unsigned int GridVertex<precision>::getX() const
	{
		return x;
	}

	template<typename precision>
	unsigned int GridVertex<precision>::getY() const
	{
		return y;
	}

	template class GridVertex<float>;
	template class GridVertex<double>;
}//graphs
