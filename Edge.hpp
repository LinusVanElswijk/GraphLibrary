#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"
#include <boost/shared_ptr.hpp>

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class Vertex;

	template <typename precision>
	struct Edge
	{
		public:
			Vertex<precision> &from, &to;
			precision cost;

		protected:
			Edge(Vertex<precision>& from, Vertex<precision>& to, const precision cost);

		friend class Vertex<precision>;
	};
} //graphs
} //extern C++

#endif /* EDGE_HPP */
