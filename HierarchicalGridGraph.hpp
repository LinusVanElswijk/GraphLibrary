#ifndef HIERARCHICAL_GRID_GRAPH_HPP
#define HIERARCHICAL_GRID_GRAPH_HPP

#include "GridGraph.hpp"

namespace graphs
{
	class HierarchicalGridmap;

	class HierarchicalGridGraph: public GridGraph
	{
		private:
			class Entrance;

			class Cluster;

		public:
			typedef boost::shared_ptr<Entrance>	   EntrancePtr;
			typedef boost::shared_ptr<Cluster>	   ClusterPtr;

			HierarchicalGridGraph(const GridGraph& gridMap, const UInt& clusterSize);
			//virtual ~HierarchicalGridMap();

			UInt getNrOfClusters() const;
			UInt getNrOfEntrances() const;

			UInt getAbstractionWidth() const;
			UInt getAbstractionHeight() const;

			Cluster& getCluster(const UInt& x, const UInt& y);

		private:
			class Cluster
			{
				public:
					Cluster(HierarchicalGridGraph& map, UInt minX, UInt minY, UInt maxX, UInt maxY);

					virtual UInt getWidth() const = 0;
					virtual UInt getHeight() const = 0;

					virtual GridVertex& getVertex(const UInt &x, const UInt &y) = 0;
					virtual const GridVertex& getVertex(const UInt &x, const UInt &y) const = 0;

				private:
					const UInt minX, minY, maxX, maxY;
			};


			void buildClusters();
		/*	void buildEntrances();
			void buildTopEntrances(const UInt& clusterX, const UInt& clusterY);
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

			const UInt clusterSize;
			const UInt abstractionWidth, abstractionHeight;

			UInt positionToClusterIndex(const UInt& x, const UInt& y) const;
			UInt clusterIndexToX(const UInt& index) const;
			UInt clusterIndexToY(const UInt& index) const;

			std::vector<ClusterPtr>  clusters;
			std::vector<EntrancePtr> entrances;
			*/
	};

}//graphs
#endif /* HIERARCHICAL_GRID_GRAPH_HPP */
