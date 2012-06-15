#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Graph.hpp"
#include "Edge.hpp"

#include <memory>
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
			typedef boost::shared_ptr<Edge<precision> > EdgePtr;

			void addEdgeTo(Vertex<precision>& vertex, const precision& cost);
			void removeEdgeTo(Vertex<precision>& Vertex);

			void addEdgeFrom(Vertex<precision>& vertex, const precision& cost);
			void removeEdgeFrom(Vertex<precision>& vertex);

			bool operator== (const Vertex<precision>& otherVertex) const;

			Graph<precision>& getGraph();
			const Graph<precision>& getGraph() const;

			static bool mutuallyConnected(const Vertex<precision>& vertexA, const Vertex<precision>& vertexB);

		protected:
			Vertex(Graph<precision>& graph);

			EdgePtr getEdgeTo(Vertex<precision>& vertex);
			EdgePtr getEdgeFrom(Vertex<precision>& vertex);

			const EdgePtr getEdgeTo(const Vertex<precision>& vertex) const;
			const EdgePtr getEdgeFrom(const Vertex<precision>& vertex) const;

		private:
			std::list<EdgePtr> outgoingEdges;
			std::list<EdgePtr> incomingEdges;

			Graph<precision>& graph;

		friend class Edge<precision>;
		friend class Graph<precision>;
	};
} //graphs
} //extern C++

#endif /* VERTEX_HPP */


