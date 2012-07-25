#ifndef HIERARCHICAL_GRID_VERTEX_HPP
#define HIERARCHICAL_GRID_VERTEX_HPP

#include "HierarchicalGridGraph.hpp"
#include "GridVertex.hpp"

extern "C++"
{
namespace graphs
{
	class HierarchicalGridGraph;

	class HierarchicalGridVertex: public GridVertex
	{
		public:
			UInt getClusterIndex() const;

			HierarchicalGridGraph& getGraph();
			const HierarchicalGridGraph& getGraph() const;

		protected:
			HierarchicalGridVertex(GridVertex& gridVertex, const UInt &clusterIndex);
			HierarchicalGridVertex(HierarchicalGridVertex& gridVertex);

			void setClusterIndex(const UInt &index);

		private:
			UInt clusterIndex;

		friend class HierarchicalGridGraph;
	};
} //graphs
} //extern C++

#endif /* GRID_VERTEX_HPP */
