#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Graph.hpp"

#include <iostream>
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

extern "C++"
{
namespace graphs
{
	class Graph;

	struct Edge;

	class Vertex
	{
		public:
			virtual UInt getIndex() const;

			void addEdgeTo(const UInt &index, const Real &cost);
			void addEdgeFrom(const UInt &index, const Real &cost);

			void removeEdgeTo(const UInt &index);
			void removeEdgeFrom(const UInt &index);

			void addEdgeTo(Vertex &vertex, const Real &cost);
			void addEdgeFrom(Vertex &vertex, const Real &cost);

			void removeEdgeTo(Vertex &vertex);
			void removeEdgeFrom(Vertex &vertex);

			void removeAllOutgoingEdges();
			void removeAllIncomingEdges();

			bool operator== (const Vertex &otherVertex) const;

			std::list<Edge> getOutgoingEdges() const;
			std::list<Edge> getIncomingEdges() const;

			Graph& getGraph();
			const Graph& getGraph() const;

			static bool mutuallyConnected(const Vertex &vertexA, const Vertex &vertexB);

			EdgePtr getEdgeTo(const UInt& index);
			EdgePtr getEdgeFrom(const UInt& index);

			EdgePtr getEdgeTo(Vertex &vertex);
			EdgePtr getEdgeFrom(Vertex &vertex);

			const EdgePtr getEdgeTo(const UInt& index) const;
			const EdgePtr getEdgeFrom(const UInt& index) const;

			const EdgePtr getEdgeTo(const Vertex &vertex) const;
			const EdgePtr getEdgeFrom(const Vertex &vertex) const;

			//const static EdgePtr NO_EDGE;

		protected:
			Vertex(Graph &graph, const UInt &index);
			Vertex(Vertex &vertex);

			void copyEdges(const Vertex& source);

		private:
			Graph& graph;

			const UInt index;

			std::list<EdgePtr> outgoingEdges;
			std::list<EdgePtr> incomingEdges;



		friend class Edge;
		friend class Graph;
	};
} //graphs
} //extern C++

#endif /* VERTEX_HPP */


