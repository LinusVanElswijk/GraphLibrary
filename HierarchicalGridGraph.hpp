#ifndef HIERARCHICAL_GRID_GRAPH_HPP
#define HIERARCHICAL_GRID_GRAPH_HPP

#include "GridGraph.hpp"
#include "HierarchicalGridVertex.hpp"

extern "C++"
{
namespace graphs
{
	class HierarchicalGridGraph: public GridGraph
	{
		public:
			class Entrance;
			typedef boost::shared_ptr<Entrance> EntrancePtr;

			class Cluster;
			typedef boost::shared_ptr<Cluster>	   ClusterPtr;

			class VertexRectangleInGraph: public graphs::VertexRectangle
			{
				public:

					VertexRectangleInGraph(HierarchicalGridGraph &graph, const UInt &minX, const UInt &minY, const UInt &maxX, const UInt &maxY);

					virtual UInt getWidth() const;
					virtual UInt getHeight() const;

					virtual UInt getTop()    const;
					virtual UInt getBottom() const;
					virtual UInt getLeft()   const;
					virtual UInt getRight()  const;

					virtual GridVertex& getVertex(const UInt &x, const UInt &y);
					virtual const GridVertex& getVertex(const UInt &x, const UInt &y) const;

					HierarchicalGridGraph& getGraph();
					const HierarchicalGridGraph& getGraph() const;

				private:
					const UInt minX, minY, maxX, maxY;
					HierarchicalGridGraph &graph;
			};

			class Entrance: public VertexRectangleInGraph
			{
				public:
					Entrance(HierarchicalGridGraph &graph, const UInt &minX, const UInt &minY, const UInt &maxX, const UInt &maxY);

			};

			class Cluster: public VertexRectangleInGraph
			{
				public:
					Cluster(HierarchicalGridGraph &graph,
							const UInt &minX, const UInt &minY, const UInt &maxX, const UInt &maxY,
							const UInt &clusterIndex
						   );

					UInt getClusterX() const;
					UInt getClusterY() const;

					void buildTopAndLeftEntrances();

					UInt getNrOfEntrances() const;

					Entrance& getEntrance(const UInt& index);
					const Entrance& getEntrance(const UInt& index) const;

				private:
					void buildTopEntrances();
					void buildLeftEntrances();

					EntrancePtr getMaximalLengthTopEntrance(UInt& x);
					EntrancePtr getMaximalLengthLeftEntrance(UInt& x);

					const UInt clusterIndex;
					std::vector<EntrancePtr> entrances;
			};

			HierarchicalGridGraph(const GridGraph& gridMap, const UInt& clusterSize);
			//virtual ~HierarchicalGridMap();

			UInt getNrOfClusters() const;
			//UInt getNrOfEntrances() const;

			UInt getAbstractionWidth() const;
			UInt getAbstractionHeight() const;

			Cluster& getCluster(const UInt& index);
			const Cluster& getCluster(const UInt& index) const;

			Cluster& getCluster(const UInt& x, const UInt& y);
			const Cluster& getCluster(const UInt& x, const UInt& y) const;

			HierarchicalGridVertex& getVertex(const UInt &index);
			const HierarchicalGridVertex& getVertex(const UInt &index) const;

			virtual GridVertex& getVertex(const UInt &x, const UInt &y);
			virtual const GridVertex& getVertex(const UInt &x, const UInt &y) const;

			UInt clusterPositionToIndex(const UInt &x, const UInt &y) const;
			UInt clusterIndexToX(const UInt &index) const;
			UInt clusterIndexToY(const UInt &index) const;

		protected:

			class HierarchicalGridVertexPromotion: public GridVertexPromotion
			{
				public:
					virtual void operator() (VertexPtr &vertex) const;
			};

			void buildClusters();
			void buildEntrances();
			void buildTopEntrances(Cluster& cluster);

		private:
			const UInt clusterSize;
			const UInt abstractionWidth, abstractionHeight;

			std::vector<ClusterPtr>  clusters;
			//boost::shared_ptr<Graph> clusterGraph;
			std::vector<EntrancePtr> entrances;

			void updateClusterIndices();

			void updateClusterIndices(Cluster& cluster, const UInt &index);

			/*void buildTopEntrances(const UInt& clusterX, const UInt& clusterY);
			void buildLeftEntrances(const UInt& clusterX, const UInt& clusterY);

			EntrancePtr getMaximalLengthEntrance(std::vector<GridVertex&> &rowA, std::vector<GridVertex&> &rowB, UInt &i, const UInt &maxI);

			class Entrance: public Rectangle
			{
				public:
					Entrance(GridVertex& vertexA, GridVertex& vertexB);

					bool isHorizontal() const;
					bool isVertical() const;

				private:

					//Vertex &transition1, &transition2;
			};

			class Cluster: public Rectangle
			{
				public:
					Cluster(GridVertex &vertexA, GridVertex &vertexB);

					std::list<EntrancePtr> entrances;
			};


			UInt positionToClusterIndex(const UInt& x, const UInt& y) const;
			UInt clusterIndexToX(const UInt& index) const;
			UInt clusterIndexToY(const UInt& index) const;
			*/


	};

}//graphs
}//extern c++
#endif /* HIERARCHICAL_GRID_GRAPH_HPP */
