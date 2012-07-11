#include "Vertex.hpp"

namespace graphs
{
	template<typename precision>
	Vertex<precision>::Vertex(Graph<precision>& graph, const typename Graph<precision>::VertexIndex &index)
	:graph(graph),
	 index(index),
	 outgoingEdges(),
	 incomingEdges()
	{
	}

	template<typename precision>
	Vertex<precision>::Vertex(Vertex<precision>& vertex)
	:graph(vertex.graph),
	 index(vertex.index),
	 outgoingEdges(vertex.outgoingEdges),
	 incomingEdges(vertex.incomingEdges)
	{
	}

	template<typename precision>
	typename Graph<precision>::VertexIndex Vertex<precision>::getIndex() const
	{
		return index;
	}

	template<typename precision>
	void Vertex<precision>::addEdgeTo(Vertex& toVertex, const precision& cost)
	{
		EdgePtr edge = getEdgeTo(toVertex);

		if(edge)
		{
			edge->cost = cost;
		}
		else
		{
			EdgePtr newEdge(new Edge<precision>(this->getIndex(), toVertex.getIndex(), cost));
			outgoingEdges.push_back(newEdge);

			toVertex.incomingEdges.push_back(newEdge);
		}
	}

	template<typename precision>
	void Vertex<precision>::addEdgeFrom(Vertex& fromVertex, const precision& cost)
	{
		EdgePtr edge = getEdgeFrom(fromVertex);

		if(edge)
		{
			edge->cost = cost;
		}
		else
		{
			EdgePtr newEdge(new Edge<precision>(fromVertex.getIndex(), this->getIndex(), cost));
			incomingEdges.push_back(newEdge);

			fromVertex.outgoingEdges.push_back(newEdge);
		}
	}

	template<typename precision>
	void Vertex<precision>::removeEdgeTo(Vertex& toVertex)
	{
		EdgePtr edge = getEdgeTo(toVertex);

		if(edge)
		{
			outgoingEdges.remove(edge);
			toVertex.incomingEdges.remove(edge);
		}
	}

	template<typename precision>
	void Vertex<precision>::removeEdgeFrom(Vertex& fromVertex)
	{
		EdgePtr edge = getEdgeFrom(fromVertex);

		if(edge)
		{
			incomingEdges.remove(edge);
			fromVertex.outgoingEdges.remove(edge);
		}
	}

	template<typename precision>
	bool Vertex<precision>::operator== (const Vertex& otherVertex) const
	{
		return this == &otherVertex;
	}

	template<typename precision>
	bool Vertex<precision>::mutuallyConnected(const Vertex<precision>& vertexA, const Vertex<precision>& vertexB)
	{
		EdgePtr edgeTo = vertexA.getEdgeTo(vertexB),
				edgeFrom = vertexA.getEdgeFrom(vertexB);

		const EdgePtr NO_EDGE = EdgePtr();

		return edgeTo != NO_EDGE && edgeFrom != NO_EDGE;
	}

	template<typename precision>
	Graph<precision>& Vertex<precision>::getGraph()
	{
		return graph;
	}

	template<typename precision>
	const Graph<precision>& Vertex<precision>::getGraph() const
	{
		return graph;
	}

	template<typename precision>
	typename std::list<typename Vertex<precision>::EdgePtr >::const_iterator Vertex<precision>::getEdgeIterator() const
	{
		return outgoingEdges.begin();
	}

	template<typename precision>
	std::list<Edge<precision> > Vertex<precision>::getOutgoingEdges() const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		std::list<Edge<precision> > edges;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			edges.push_back(**i);
		}

		return edges;
	}

	template<typename precision>
	std::list<Edge<precision> > Vertex<precision>::getIncomingEdges() const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		std::list<Edge<precision> > edges;

		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			edges.push_back(**i);
		}

		return edges;
	}

	template<typename precision>
	typename Vertex<precision>::EdgePtr Vertex<precision>::getEdgeTo(Vertex& vertex)
	{
		typedef typename std::list<EdgePtr>::iterator iterator;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			EdgePtr edge = *i;

			if( edge->toIndex == vertex.getIndex())
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	template<typename precision>
	typename Vertex<precision>::EdgePtr Vertex<precision>::getEdgeFrom(Vertex& vertex)
	{
		typedef typename std::list<EdgePtr>::iterator iterator;

		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			EdgePtr edge = *i;

			if( edge->fromIndex == vertex.getIndex())
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	template<typename precision>
	const typename Vertex<precision>::EdgePtr Vertex<precision>::getEdgeTo(const Vertex& vertex) const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			const EdgePtr edge = *i;

			if( edge->toIndex == vertex.getIndex())
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	template<typename precision>
	const typename Vertex<precision>::EdgePtr Vertex<precision>::getEdgeFrom(const Vertex& vertex) const
	{
		typedef typename std::list<EdgePtr>::const_iterator iterator;

		for(iterator i = incomingEdges.begin(); i != incomingEdges.end(); i++)
		{
			const EdgePtr edge = *i;

			if( edge->fromIndex == vertex.getIndex())
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	template class Vertex<float>;
	template class Vertex<double>;
}//graphs
