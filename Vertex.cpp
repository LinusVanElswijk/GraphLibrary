#include "Vertex.hpp"

namespace graphs
{
	template<typename precision>
	Vertex<precision>::Vertex(Graph<precision>& graph)
	:graph(graph)
	{
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
			new Edge<precision>(*this, toVertex, cost);
		}
	}

	template<typename precision>
	void Vertex<precision>::removeEdgeTo(Vertex& toVertex)
	{
		EdgePtr edge = getEdgeTo(toVertex);

		if(edge)
		{
			outgoingEdges.remove(edge);
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
		return vertexA.getEdgeTo(vertexB) != 0 && vertexA.getEdgeFrom(vertexB) != 0;
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
	typename Vertex<precision>::EdgePtr Vertex<precision>::getEdgeTo(Vertex& vertex)
	{
		typedef typename std::list<EdgePtr>::iterator iterator;

		for(iterator i = outgoingEdges.begin(); i != outgoingEdges.end(); i++)
		{
			EdgePtr edge = *i;

			if( edge->to == vertex)
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

			if( edge->from == vertex)
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

			if( edge->to == vertex)
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

			if( edge->from == vertex)
			{
				return edge;
			}
		}

		return EdgePtr();
	}

	template class Vertex<float>;
	template class Vertex<double>;
}//graphs
