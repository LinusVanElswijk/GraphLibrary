#include "Graph.hpp"

namespace graphs
{
	template<typename precision>
	Graph<precision>::Graph(const unsigned int& size)
    :vertices()
	{
		initializeVertices(size);
	}

	template<typename precision>
	Graph<precision>::~Graph()
	{
	}

	template<typename precision>
	Vertex<precision>& Graph<precision>::getVertex(const VertexIndex& index)
	{
		return (*vertices.at(index));
	}

	template<typename precision>
	const Vertex<precision>& Graph<precision>::getVertex(const VertexIndex& index) const
	{
		return (*vertices.at(index));
	}

	template<typename precision>
	void Graph<precision>::addEdge(Vertex<precision> &vertexA, Vertex<precision> &vertexB, const precision& cost)
	{
		vertexA.addEdgeTo(vertexB, cost);
	}

	template<typename precision>
	void Graph<precision>::addBidirectionalEdge(Vertex<precision> &vertexA, Vertex<precision> &vertexB, const precision& cost)
	{
		addEdge(vertexA, vertexB, cost);
		addEdge(vertexB, vertexA, cost);
	}

	template<typename precision>
	unsigned int Graph<precision>::getNrOfVertices()
	{
		return vertices.size();
	}

	template<typename precision>
	void Graph<precision>::initializeVertices(const unsigned int& nrOfVertices)
	{
		vertices.reserve(nrOfVertices);

		for(VertexIndex i = 0; i < nrOfVertices; i++)
		{
			VertexPtr vertex(new Vertex<precision>(*this, i));
			vertices.push_back(vertex);
		}
	}

	template class Graph<float>;
	template class Graph<double>;
}//graphs
