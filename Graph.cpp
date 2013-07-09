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

    Vertex& Graph::addVertex() {
        VertexPtr vertex(new Vertex(*this, vertices.size()));
        vertices.push_back(vertex);
        return *vertex;
    }


    void Graph::removeVertex(Vertex& vertex) {
        int i = 0;
        int size = vertices.size();

        for(auto iterator = vertices.begin(); iterator != vertices.end(); iterator++, i++) {
            if(&(**iterator) == &vertex) {
                vertex.removeAllIncomingEdges();
                vertex.removeAllOutgoingEdges();
                vertices.erase(iterator);
                break;
            }
        }
    }

}//graphs
