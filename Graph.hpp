#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vertex.hpp"
#include "Edge.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class Vertex;

	template <typename precision>
	class EdgeMap;

	template <typename precision>
	class Graph
	{
		public:
			typedef boost::shared_ptr<Vertex<precision> > EdgePtr;
			typedef boost::shared_ptr<Vertex<precision> > VertexPtr;
			typedef typename std::vector<VertexPtr>::size_type VertexIndex;

			Graph(const unsigned int& size);
			//Graph(const Graph<precision> &graph);

			virtual ~Graph();

			virtual Vertex<precision>& getVertex(const VertexIndex& index);
			virtual const Vertex<precision>& getVertex(const VertexIndex& index) const;

			void addEdge(Vertex<precision> &vertexA, Vertex<precision> &vertexB, const precision& cost);
			void addBidirectionalEdge(Vertex<precision> &vertexA, Vertex<precision> &vertexB, const precision& cost);

			unsigned int getNrOfVertices();

		protected:
			virtual void initializeVertices(const unsigned int& nrOfVertices);
			std::vector<VertexPtr> vertices;
	};
} //graphs
} //extern C++

#endif /* GRAPH_HPP */


