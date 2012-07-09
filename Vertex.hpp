#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Graph.hpp"
#include "Edge.hpp"

#include <iostream>
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class Graph;

	template <typename precision>
	struct Edge;

	template <typename precision>
	class Vertex
	{
		public:
			typedef boost::shared_ptr< Edge<precision> > EdgePtr;

			typename Graph<precision>::VertexIndex getIndex() const;

			virtual void addEdgeTo(Vertex<precision>& vertex, const precision& cost);
			void removeEdgeTo(Vertex<precision>& Vertex);

			void addEdgeFrom(Vertex<precision>& vertex, const precision& cost);
			void removeEdgeFrom(Vertex<precision>& vertex);

			bool operator== (const Vertex<precision>& otherVertex) const;

			typename std::list<typename Vertex<precision>::EdgePtr >::const_iterator getEdgeIterator() const;

			std::list<Edge<precision> > getOutgoingEdges() const;
			std::list<Edge<precision> > getIncomingEdges() const;

			Graph<precision>& getGraph();
			const Graph<precision>& getGraph() const;

			static bool mutuallyConnected(const Vertex<precision>& vertexA, const Vertex<precision>& vertexB);

			const static EdgePtr NO_EDGE;

		protected:
			Vertex(Graph<precision>& graph, const typename Graph<precision>::VertexIndex &index);

			EdgePtr getEdgeTo(Vertex<precision>& vertex);
			EdgePtr getEdgeFrom(Vertex<precision>& vertex);

			const EdgePtr getEdgeTo(const Vertex<precision>& vertex) const;
			const EdgePtr getEdgeFrom(const Vertex<precision>& vertex) const;

		private:
			Graph<precision>& graph;

			const typename Graph<precision>::VertexIndex index;


			std::list<EdgePtr> outgoingEdges;
			std::list<EdgePtr> incomingEdges;

		friend class Edge<precision>;
		friend class Graph<precision>;
	};
} //graphs
} //extern C++

#endif /* VERTEX_HPP */


