#ifndef GRAPH_TYPES_HPP
#define GRAPH_TYPES_HPP

#include <memory>
#include <vector>

namespace graphs
{
	typedef double Real;
	typedef unsigned int UInt;

	class Edge;
	class Vertex;
    class GridVertex;

	class VertexRectangle;

    typedef std::shared_ptr<Vertex> VertexPtr;
    typedef std::shared_ptr<Edge> EdgePtr;
    typedef std::shared_ptr<const Edge> ConstEdgePtr;
    typedef std::shared_ptr<GridVertex> GridVertexPtr;
}

#endif
