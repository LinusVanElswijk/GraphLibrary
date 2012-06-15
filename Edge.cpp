#include "GridGraph.hpp"

namespace graphs
{
	template<typename precision>
	Edge<precision>::Edge(Vertex<precision>& from, Vertex<precision>& to, const precision cost)
	:from(from),
	 to(to),
	 cost(cost)
	{
	}

	template struct Edge<float>;
	template struct Edge<double>;
}//graphs
