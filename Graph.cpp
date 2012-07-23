#include "Graph.hpp"

namespace graphs
{
	Graph::Graph(const UInt &size)
    :vertices()
	{
		initializeVertices(size);
	}

	Graph::Graph(const Graph& otherGraph, bool copyEdges)
	:vertices()
	{
		initializeVertices(otherGraph.getNrOfVertices());

		if(copyEdges)
		{
			copyEdgeTopology(otherGraph);
		}
	}

	Graph::~Graph()
	{
	}

	Vertex& Graph::getVertex(const UInt &index)
	{
		return (*vertices.at(index));
	}

	const Vertex& Graph::getVertex(const UInt &index) const
	{
		return (*vertices.at(index));
	}

	void Graph::addEdge(Vertex &vertexA, Vertex &vertexB, const Real &cost)
	{
		vertexA.addEdgeTo(vertexB, cost);
	}

	void Graph::addBidirectionalEdge(Vertex &vertexA, Vertex &vertexB, const Real &cost)
	{
		addEdge(vertexA, vertexB, cost);
		addEdge(vertexB, vertexA, cost);
	}

	UInt Graph::getNrOfVertices() const
	{
		return (UInt)vertices.size();
	}

	void Graph::initializeVertices(const UInt &nrOfVertices)
	{

		vertices.reserve((VectorSize)nrOfVertices);

		for(UInt i = 0; i < nrOfVertices; i++)
		{
			VertexPtr vertex(new Vertex(*this, i));
			vertices.push_back(vertex);
		}
	}

	void Graph::copyEdgeTopology(const Graph& otherGraph)
	{
		const UInt NR_OF_VERTICES = otherGraph.getNrOfVertices();

		for(UInt i = 0; i < NR_OF_VERTICES; i++)
		{
			this->getVertex(i).copyEdges(otherGraph.getVertex(i));
		}
	}

	void Graph::promoteVertices(const VertexPromoteFunction &promoteVertex)
	{
		typedef typename std::vector<VertexPtr>::iterator Iterator;

		for(Iterator i = vertices.begin(); i != vertices.end(); i++)
		{
			promoteVertex(*i);
		}
	}
}//graphs
