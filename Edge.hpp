#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"
#include "Graph.hpp"
#include <boost/shared_ptr.hpp>

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class Graph;

	template <typename precision>
	struct Edge
	{
		public:
			typedef typename Graph<precision>::VertexIndex VertexIndex;

			Edge();
			Edge(const VertexIndex &fromIndex, const VertexIndex &toIndex, const precision &cost);

			//Edge<precision>& operator= (const Edge<precision>& edge);

			bool operator== (const Edge<precision>& edge) const;

			VertexIndex fromIndex, toIndex;
			precision cost;
	};
} //graphs
} //extern C++

#endif /* EDGE_HPP */
