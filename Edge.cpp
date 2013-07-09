#include "Edge.hpp"

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

	Edge::Edge(const UInt &fromIndex, const UInt &toIndex, const Real &cost)
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

	bool Edge::operator== (const Edge &edge) const
	{
		return fromIndex == edge.fromIndex && toIndex == edge.toIndex && cost == edge.cost;
	}
}//graphs
