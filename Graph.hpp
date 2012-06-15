#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vertex.hpp"
#include "Edge.hpp"

#include <boost/shared_ptr.hpp>
#include <vector>

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class Graph
	{
		public:
			typedef boost::shared_ptr<Vertex<precision> > VertexPtr;

			Graph(const unsigned int& size);
			Graph(const Graph<precision> &graph);

			virtual ~Graph();

			virtual Vertex<precision>& getVertex(const unsigned int& index);
			virtual const Vertex<precision>& getVertex(const unsigned int& index) const;

			void addEdge(Vertex<precision> &vertexA, Vertex<precision> &vertexB, const precision& cost);
			void addBidirectionalEdge(Vertex<precision> &vertexA, Vertex<precision> &vertexB, const precision& cost);

			unsigned int getNrOfVertices();

		protected:
			virtual void initializeVertices(const unsigned int& nrOfVertices);
			std::vector<VertexPtr> vertices;

		private:

	};
} //graphs
} //extern C++

#endif /* GRAPH_HPP */


