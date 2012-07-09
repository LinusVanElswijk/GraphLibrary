#include "GridGraph.hpp"

namespace graphs
{
/*
	template<typename precision>
	Edge<precision>::Edge()
	:fromIndex(0),
	 toIndex(0),
	 cost(0)
	{
	}*/

	template<typename precision>
	Edge<precision>::Edge(const VertexIndex &fromIndex, const VertexIndex &toIndex, const precision &cost)
	:fromIndex(fromIndex),
	 toIndex(toIndex),
	 cost(cost)
	{
	}
	/*
	template<typename precision>
	Edge<precision>& Edge<precision>::operator= (const Edge<precision>& edge)
	{
		fromIndex = edge.fromIndex;
		toIndex = edge.toIndex;
		cost = edge.cost;

		return *this;
	}*/

	template<typename precision>
	bool Edge<precision>::operator== (const Edge<precision>& edge) const
	{
		return fromIndex == edge.fromIndex && toIndex == edge.toIndex && cost == edge.cost;
	}

	template struct Edge<float>;
	template struct Edge<double>;
}//graphs
