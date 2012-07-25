#ifndef GRAPH_TYPES_HPP
#define GRAPH_TYPES_HPP

#include <boost/shared_ptr.hpp>
#include <vector>

namespace graphs
{
	typedef double Real;
	typedef unsigned int UInt;

	class Edge;
	class Vertex;
	class GridVertex;
	class HierarchicalGridVertex;

	class VertexRectangle;

	typedef boost::shared_ptr<Vertex> VertexPtr;
	typedef boost::shared_ptr<Edge> EdgePtr;
	typedef boost::shared_ptr<GridVertex> GridVertexPtr;
	typedef boost::shared_ptr<HierarchicalGridVertex> HierarchicalGridVertexPtr;
}

#endif
