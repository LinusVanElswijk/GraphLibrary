#include "HierarchicalGridVertex.hpp"

namespace graphs
{
	UInt HierarchicalGridVertex::getClusterIndex() const
	{
		return clusterIndex;
	}

	HierarchicalGridGraph& HierarchicalGridVertex::getGraph()
	{
		GridGraph &gridGraph = GridVertex::getGraph();
		return static_cast<HierarchicalGridGraph&>( gridGraph );
	}

	const HierarchicalGridGraph& HierarchicalGridVertex::getGraph() const
	{
		const GridGraph &gridGraph = GridVertex::getGraph();
		return static_cast<const HierarchicalGridGraph&>( gridGraph );
	}

	HierarchicalGridVertex::HierarchicalGridVertex(GridVertex& gridVertex, const UInt &clusterIndex)
	:GridVertex(gridVertex),
	 clusterIndex(clusterIndex)
	{

	}

	HierarchicalGridVertex::HierarchicalGridVertex(HierarchicalGridVertex& hierarchicalGridVertex)
	:GridVertex(hierarchicalGridVertex),
	 clusterIndex(clusterIndex)
	{

	}

	void HierarchicalGridVertex::setClusterIndex(const UInt &index)
	{
		clusterIndex = index;
	}
}
