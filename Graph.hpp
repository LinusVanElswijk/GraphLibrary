#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

#include "Types.hpp"

extern "C++"
{
namespace graphs
{
	class Graph
	{
		public:
			explicit Graph(const UInt &size);
			Graph(const Graph& otherGraph, bool copyEdges = true);

			virtual ~Graph();

			Vertex& getVertex(const UInt &index);
			const Vertex& getVertex(const UInt &index) const;

			void addEdge(Vertex &vertexA, Vertex &vertexB, const Real &cost);
			void addBidirectionalEdge(Vertex &vertexA, Vertex &vertexB, const Real &cost);

			UInt getNrOfVertices() const;

		protected:
			class VertexPromoteFunction
			{
				public:
					virtual void operator() (VertexPtr &vertex) const = 0;
			};

            void promoteVertices(const VertexPromoteFunction &promoteVertex);

            void copyEdgeTopology(const Graph& othergraph);

            Vertex& addVertex();
            void removeVertex(Vertex& vertex);


		private:
            void initializeVertices(const UInt &nrOfVertices);


		    typedef std::vector<VertexPtr>::size_type VectorSize;
		    std::vector<VertexPtr> vertices;
		    std::vector<EdgePtr> edges;
	};
} //graphs
} //extern C++

#include "Vertex.hpp"
#include "Edge.hpp"


#endif /* GRAPH_HPP */


