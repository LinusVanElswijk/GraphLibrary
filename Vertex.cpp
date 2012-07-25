#include "Vertex.hpp"

namespace graphs
{
	Vertex::Vertex(Graph &graph, const UInt &index)
	:graph(graph),
	 index(index),
	 outgoingEdges(),
	 incomingEdges()
	{
	}

	Vertex::Vertex(Vertex &vertex)
	:graph(vertex.graph),
	 index(vertex.index),
	 outgoingEdges(vertex.outgoingEdges),
	 incomingEdges(vertex.incomingEdges)
	{
	}

	UInt Vertex::getIndex() const
	{
		return index;
	}

	void Vertex::addEdgeTo(const UInt &index, const Real &cost)
	{
		EdgePtr edge = getEdgeTo(index);

		if(edge)
		{
			edge->cost = cost;
		}
		else
		{
			EdgePtr newEdge(new Edge(this->getIndex(), index, cost));
			outgoingEdges.push_back(newEdge);

            graph.getVertex(index).incomingEdges.push_back(newEdge);
		}
	}

	void Vertex::addEdgeTo(Vertex &toVertex, const Real &cost)
	{
		addEdgeTo(toVertex.getIndex(), cost);
	}

	void Vertex::addEdgeFrom(const UInt &index, const Real &cost)
	{
		EdgePtr edge = getEdgeFrom(index);

		if(edge)
		{
			edge->cost = cost;
		}
		else
		{
			EdgePtr newEdge(new Edge(index, this->getIndex(), cost));
			incomingEdges.push_back(newEdge);

			graph.getVertex(index).outgoingEdges.push_back(newEdge);
		}
	}

	void Vertex::addEdgeFrom(Vertex &fromVertex, const Real &cost)
	{
		addEdgeFrom(fromVertex.getIndex(), cost);
	}

	void Vertex::removeEdgeTo(const UInt &index)
	{
		EdgePtr edge = getEdgeTo(index);

		if(edge)
		{
			outgoingEdges.remove(edge);
			graph.getVertex(index).incomingEdges.remove(edge);
		}
	}

	void Vertex::removeEdgeTo(Vertex &toVertex)
	{
		removeEdgeTo(toVertex.getIndex());
	}

	void Vertex::removeEdgeFrom(const UInt &index)
	{
		EdgePtr edge = getEdgeFrom(index);

		if(edge)
		{
			incomingEdges.remove(edge);
			graph.getVertex(index).outgoingEdges.remove(edge);
		}
	}

	void Vertex::removeEdgeFrom(Vertex &fromVertex)
	{
		removeEdgeFrom(fromVertex.getIndex());
	}

	void Vertex::removeAllOutgoingEdges()
	{
		outgoingEdges.clear();
	}

	void Vertex::removeAllIncomingEdges()
	{
		incomingEdges.clear();
	}

	bool Vertex::operator== (const Vertex &otherVertex) const
	{
		return this == &otherVertex;
	}

	bool Vertex::mutuallyConnected(const Vertex &vertexA, const Vertex &vertexB)
	{
		EdgePtr edgeTo = vertexA.getEdgeTo(vertexB),
				edgeFrom = vertexA.getEdgeFrom(vertexB);

		const EdgePtr NO_EDGE = EdgePtr();

		return edgeTo != NO_EDGE && edgeFrom != NO_EDGE;
	}

	Graph& Vertex::getGraph()
	{
		return graph;
	}

	const Graph& Vertex::getGraph() const
	{
		return graph;
	}

	std::list<Edge> Vertex::getOutgoingEdges() const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		std::list<Edge> edges;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			edges.push_back(**i);
		}

		return edges;
	}

	std::list<Edge> Vertex::getIncomingEdges() const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		std::list<Edge > edges;

		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			edges.push_back(**i);
		}

		return edges;
	}

	EdgePtr Vertex::getEdgeTo(const UInt &index)
	{
		typedef typename std::list<EdgePtr>::iterator iterator;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			EdgePtr edge = *i;

			if( edge->toIndex == index)
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	EdgePtr Vertex::getEdgeTo(Vertex &vertex)
	{
		return getEdgeTo(vertex.getIndex());
	}

	EdgePtr Vertex::getEdgeFrom(const UInt &index)
	{
		typedef typename std::list<EdgePtr>::iterator iterator;

		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			EdgePtr edge = *i;

			if( edge->fromIndex == index)
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	EdgePtr Vertex::getEdgeFrom(Vertex &vertex)
	{
		return getEdgeFrom(vertex.getIndex());
	}

	const EdgePtr Vertex::getEdgeTo(const UInt &index) const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			const EdgePtr edge = *i;

			if(edge->toIndex == index)
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	const EdgePtr Vertex::getEdgeTo(const Vertex &vertex) const
	{
		return getEdgeTo(vertex.getIndex());
	}

	const EdgePtr Vertex::getEdgeFrom(const UInt &index) const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			const EdgePtr edge = *i;

			if( edge->fromIndex == index)
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	const EdgePtr Vertex::getEdgeFrom(const Vertex &vertex) const
	{
		return getEdgeFrom(vertex.getIndex());
	}

	void Vertex::copyEdges(const Vertex& source)
	{
		std::list<Edge> outgoingEdges = source.getOutgoingEdges();
		std::list<Edge> incomingEdges = source.getIncomingEdges();

		removeAllOutgoingEdges();
		typedef typename std::list<Edge>::const_iterator iterator;
		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			if(index <= i->toIndex);
			addEdgeTo(i->toIndex, i->cost);
		}

		removeAllIncomingEdges();
		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			if(index < i->fromIndex);
			addEdgeFrom(i->fromIndex, i->cost);
		}
	}

}//graphs
