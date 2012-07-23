#ifndef EDGE_HPP
#define EDGE_HPP

#include "Graph.hpp"

#include <boost/shared_ptr.hpp>

extern "C++"
{
namespace graphs
{
	class Graph;

	struct Edge
	{
		public:
			Edge();
			Edge(const UInt &fromIndex, const UInt &toIndex, const Real &cost);

			//Edge<precision>& operator= (const Edge<precision>& edge);

			bool operator== (const Edge& edge) const;

			UInt fromIndex, toIndex;
			Real cost;
	};
} //graphs
} //extern C++

#endif /* EDGE_HPP */
