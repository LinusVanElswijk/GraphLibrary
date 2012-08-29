#include <iostream>

#include "GridGraph.hpp"

namespace graphs
{
	GridGraph::GridGraph( const UInt &width, const UInt &height, const InitialConnections &connections )
	:Graph(width*height),
	 width(width),
     height(height)
	{
		GridVertexPromotion promoteFunction;
		promoteVertices( promoteFunction );

		//initializeEdges(connections);
	}

	GridGraph::GridGraph( const GridGraph &otherGraph, bool copyEdges )
	:Graph(otherGraph, false),
	 width(otherGraph.width),
	 height(otherGraph.height)
	{
		GridVertexPromotion promoteFunction;
		promoteVertices( promoteFunction );

		if(copyEdges)
		{
			copyEdgeTopology(otherGraph);
		}
	}

	GridVertex& GridGraph::getVertex(const UInt &index)
	{
		Vertex& vertex = Graph::getVertex(index);
		return static_cast< GridVertex& >(vertex);
	}

	const GridVertex& GridGraph::getVertex(const UInt &index) const
	{
		const Vertex& vertex = Graph::getVertex(index);
		return static_cast<const GridVertex& >(vertex);
	}

	GridVertex& GridGraph::getVertex(const UInt &x, const UInt &y)
	{
		return getVertex( positionToIndex(x, y) );
	}

	const GridVertex& GridGraph::getVertex(const UInt &x, const UInt &y) const
	{
		return getVertex( positionToIndex(x, y) );
	}

	UInt GridGraph::getWidth() const
	{
		return width;
	}

	UInt GridGraph::getHeight() const
	{
		return height;
	}

	UInt GridGraph::getTop() const
	{
		return 0;
	}

	UInt GridGraph::getBottom() const
	{
		return height - 1;
	}

	UInt GridGraph::getLeft() const
	{
		return 0;
	}

	UInt GridGraph::getRight() const
	{
		return width - 1;
	}

	void GridGraph::GridVertexPromotion::operator() (VertexPtr &vertex) const
	{
		GridGraph &graph = static_cast< GridGraph& >( vertex->getGraph() );

		const UInt	X = graph.indexToX(vertex->getIndex()),
					Y = graph.indexToY(vertex->getIndex());

		GridVertexPtr gridVertex(new GridVertex(*vertex, X, Y));

		vertex = gridVertex;
	}

	void GridGraph::initializeEdges(const InitialConnections & connections)
	{
		if(connections == UNCONNECTED)
		{
			return;
		}

		const Real SQRT_2 = (Real)std::sqrt(2.0);

		for(UInt x = 1; x < width; x++)
		{
			for(UInt y = 1; y < height; y++)
			{
				this->addBidirectionalEdge(this->getVertex(x, y), this->getVertex(x-1, y), (Real)1.0);
				this->addBidirectionalEdge(this->getVertex(x, y), this->getVertex(x, y-1), (Real)1.0);
				this->addBidirectionalEdge(this->getVertex(x, y), this->getVertex(x-1, y-1), SQRT_2);
				this->addBidirectionalEdge(this->getVertex(x-1, y), this->getVertex(x, y-1), SQRT_2);
			}
		}

		if(connections == EIGHT_WAY)
		{
			for(UInt x = 1; x < width; x++)
			{
				this->addBidirectionalEdge(this->getVertex(x,0), this->getVertex(x-1, 0), (Real)1.0);
			}

			for(UInt y = 1; y < height; y++)
			{
				this->addBidirectionalEdge(this->getVertex(0,y), this->getVertex(0, y-1), (Real)1.0);
			}
		}
	}

	UInt GridGraph::positionToIndex(const UInt &x, const UInt &y) const
	{
		return x + y * width;
	}

	UInt GridGraph::indexToX(const UInt &index) const
	{
		return index % width;
	}

	UInt GridGraph::indexToY(const UInt &index) const
	{
		return index / width;
	}

}//graphs
