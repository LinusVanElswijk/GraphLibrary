#include "HierarchicalGridGraph.hpp"

namespace graphs
{
	HierarchicalGridGraph::HierarchicalGridGraph(const GridGraph& gridMap, const UInt& clusterSize)
	:GridGraph(gridMap),
	 clusterSize(clusterSize),
	 abstractionWidth((this->getWidth() + clusterSize - 1) / clusterSize),
	 abstractionHeight((this->getHeight() + clusterSize - 1) / clusterSize),
	 clusters(),
	 entrances()
	{
		HierarchicalGridVertexPromotion promoteFunction;
		promoteVertices( promoteFunction );

		buildClusters();
		buildEntrances();
	}

	UInt HierarchicalGridGraph::getNrOfClusters() const
	{
		return clusters.size();
	}

	HierarchicalGridGraph::Cluster& HierarchicalGridGraph::getCluster(const UInt& index)
	{
		return *clusters.at(index);
	}

	const HierarchicalGridGraph::Cluster& HierarchicalGridGraph::getCluster(const UInt& index) const
	{
		return *clusters.at(index);
	}

	HierarchicalGridGraph::Cluster& HierarchicalGridGraph::getCluster(const UInt& x, const UInt& y)
	{
		return *clusters.at(clusterPositionToIndex(x, y));
	}

	const HierarchicalGridGraph::Cluster& HierarchicalGridGraph::getCluster(const UInt& x, const UInt& y) const
	{
		return *clusters.at(clusterPositionToIndex(x, y));
	}

	UInt  HierarchicalGridGraph::clusterPositionToIndex(const UInt &x, const UInt &y) const
	{
		return x + y * abstractionWidth;
	}

	UInt  HierarchicalGridGraph::clusterIndexToX(const UInt &index) const
	{
		return index % abstractionWidth;
	}

	UInt  HierarchicalGridGraph::clusterIndexToY(const UInt &index) const
	{
		return index / abstractionWidth;
	}

	void HierarchicalGridGraph::buildClusters()
	{
		const UInt DELTA = clusterSize - 1,
		           MAX_X = this->getWidth()  - 1,
		           MAX_Y = this->getHeight() - 1;

		for(UInt y = 0, index = 0; y < this->getHeight(); y+=clusterSize)
		{
			for(UInt x = 0; x < this->getWidth(); x+=clusterSize, index++)
			{
				const UInt x2 = std::min(x + DELTA, MAX_X),
						   y2 = std::min(y + DELTA, MAX_Y);

				ClusterPtr ptr(new Cluster(*this, x, y, x2, y2, index));
				clusters.push_back(ptr);
			}
		}

		updateClusterIndices();
	}

	void HierarchicalGridGraph::updateClusterIndices()
	{
		const UInt NR_OF_CLUSTERS = getNrOfClusters();

		for(UInt i = 0; i < NR_OF_CLUSTERS; i++)
		{
			updateClusterIndices(getCluster(i), i);
		}
	}

	void HierarchicalGridGraph::updateClusterIndices(Cluster &cluster, const UInt &index)
	{
		const UInt WIDTH  = cluster.getWidth(),
		           HEIGHT = cluster.getHeight();

		for(UInt x = 0; x < WIDTH; x++)
		{
			for(UInt y = 0; y < HEIGHT; y++)
			{
				HierarchicalGridVertex &hVertex = static_cast<HierarchicalGridVertex&>(cluster.getVertex(x, y));
				hVertex.setClusterIndex(index);
			}
		}
	}

	void HierarchicalGridGraph::HierarchicalGridVertexPromotion::operator() (VertexPtr &vertex) const
	{
		GridVertexPromotion::operator() (vertex);

		HierarchicalGridVertexPtr hierarchicalGridVertex
			(new HierarchicalGridVertex(static_cast<GridVertex&>(*vertex), 0) );

		vertex = hierarchicalGridVertex;
	}

	HierarchicalGridVertex& HierarchicalGridGraph::getVertex(const UInt &index)
	{
		GridVertex& vertex = GridGraph::getVertex(index);
		return static_cast< HierarchicalGridVertex& >(vertex);
	}

	const HierarchicalGridVertex& HierarchicalGridGraph::getVertex(const UInt &index) const
	{
		const GridVertex& vertex = GridGraph::getVertex(index);
		return static_cast<const HierarchicalGridVertex& >(vertex);
	}

	GridVertex& HierarchicalGridGraph::getVertex(const UInt &x, const UInt &y)
	{
		return GridGraph::getVertex(x, y);
	}

	const GridVertex& HierarchicalGridGraph::getVertex(const UInt &x, const UInt &y) const
	{
		return GridGraph::getVertex(x, y);
	}

	UInt HierarchicalGridGraph::getAbstractionWidth() const
	{
		return abstractionWidth;
	}

	UInt HierarchicalGridGraph::getAbstractionHeight() const
	{
		return abstractionHeight;
	}

	void HierarchicalGridGraph::buildEntrances()
	{
		for(UInt i = 0; i < clusters.size(); i++)
		{
			Cluster& cluster = *clusters.at(i);
			cluster.buildTopAndLeftEntrances();
		}
	}

	/*
	template <typename precision>
	HierarchicalGridMap<precision>::~HierarchicalGridMap()
	{
		// TODO Auto-generated destructor stub
	}
	/


	UInt HierarchicalGridGraph::getNrOfEntrances() const
	{
		return entrances.size();
	}









	HierarchicalGridGraph::EntrancePtr HierarchicalGridGraph::getMaximalLengthEntrance(std::vector<GridVertex&> &rowA, std::vector<GridVertex&> &rowB, UInt &i, const UInt &maxI)
	{
		if( !Vertex::mutuallyConnected(rowA.at(i), rowB.at(i)) )
		{
			EntrancePtr();
		}
		else
		{
			unsigned int min = i;

			while(i < maxI)
			{
				UInt iNext = i + 1;
				if( Vertex::mutuallyConnected(rowA.at(iNext), rowB.at(iNext)) &&
					Vertex::mutuallyConnected(rowA.at(i), rowA.at(iNext)) &&
					Vertex::mutuallyConnected(rowB.at(i), rowB.at(iNext))
				)

			   i++;
			}

			unsigned int minX = std::min(rowA.at(min).getX(), rowB.at(min).getX());
			unsigned int maxX = std::max(rowA.at(i).getX(), rowB.at(i).getX());
			unsigned int minY = std::min(rowA.at(min).getY(), rowB.at(min).getY());
			unsigned int maxY = std::max(rowA.at(i).getY(), rowB.at(i).getY());

			GridGraph& map = rowA.at(min).getGraph();

			GridVertex  &topLeft = map.getVertex(minX, minY),
					    &bottomRight = map.getVertex(maxX, maxY);

			return EntrancePtr(new Entrance(topLeft, bottomRight));
		}

		return EntrancePtr();
	}

	void HierarchicalGridGraph::buildLeftEntrances(const UInt& clusterX, const UInt& clusterY)
	{

	}

	UInt HierarchicalGridGraph::positionToClusterIndex(const UInt& x, const UInt& y) const
	{
		return std::size_t(x + y * (abstractionWidth));
	}

	UInt HierarchicalGridGraph::clusterIndexToX(const UInt& index) const
	{
		return index % (abstractionWidth);
	}

	UInt HierarchicalGridGraph::clusterIndexToY(const UInt& index) const
	{
		return index / (abstractionWidth);
	}
	*/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// class VertexRectangleInGraph

	HierarchicalGridGraph::VertexRectangleInGraph::VertexRectangleInGraph( HierarchicalGridGraph& graph,
																		   const UInt &minX, const UInt &minY, const UInt &maxX, const UInt &maxY
																		 )
	:minX(minX),
	 minY(minY),
	 maxX(maxX),
	 maxY(maxY),
	 graph(graph)
	{
	}

	UInt HierarchicalGridGraph::VertexRectangleInGraph::getWidth() const
	{
		return maxX - minX + 1;
	}

	UInt HierarchicalGridGraph::VertexRectangleInGraph::getHeight() const
	{
		return maxY - minY + 1;
	}

	UInt HierarchicalGridGraph::VertexRectangleInGraph::getTop() const
	{
		return minY;
	}

	UInt HierarchicalGridGraph::VertexRectangleInGraph::getBottom() const
	{
		return maxY;
	}

	UInt HierarchicalGridGraph::VertexRectangleInGraph::getLeft() const
	{
		return minX;
	}

	UInt HierarchicalGridGraph::VertexRectangleInGraph::getRight() const
	{
		return maxX;
	}

	GridVertex& HierarchicalGridGraph::VertexRectangleInGraph::getVertex(const UInt &x, const UInt &y)
	{
		return graph.getVertex(minX + x, minY + y);
	}

	const GridVertex& HierarchicalGridGraph::VertexRectangleInGraph::getVertex(const UInt &x, const UInt &y) const
	{
		return graph.getVertex(minX + x, minY + y);
	}

	HierarchicalGridGraph& HierarchicalGridGraph::VertexRectangleInGraph::getGraph()
	{
		return graph;
	}

	const HierarchicalGridGraph& HierarchicalGridGraph::VertexRectangleInGraph::getGraph() const
	{
		return graph;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// class Entrance

	HierarchicalGridGraph::Entrance::Entrance(HierarchicalGridGraph& graph, const UInt &minX, const UInt &minY, const UInt &maxX, const UInt &maxY)
	:VertexRectangleInGraph(graph, minX, minY, maxX, maxY)
	{

	}
	/*
	template <typename precision>
	bool HierarchicalGridMap<precision>::Entrance::isHorizontal() const
	{
		//return this->top == this->bottom+1;
	}

	template <typename precision>
	bool HierarchicalGridMap<precision>::Entrance::isVertical() const
	{
		//return this->topLeft.getX() == this->bottomRight.getX()-1;
	}
	/
	*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// class Cluster

	HierarchicalGridGraph::Cluster::Cluster(HierarchicalGridGraph& graph, const UInt &minX, const UInt &minY, const UInt &maxX, const UInt &maxY, const UInt &index)
	:VertexRectangleInGraph(graph, minX, minY, maxX, maxY),
	 clusterIndex(index),
	 entrances()
	{
	}

	UInt HierarchicalGridGraph::Cluster::getClusterX() const
	{
		const HierarchicalGridGraph &hGraph = static_cast<const HierarchicalGridGraph&>(getGraph());
		return hGraph.clusterIndexToX(clusterIndex);
	}

	UInt HierarchicalGridGraph::Cluster::getClusterY() const
	{
		const HierarchicalGridGraph &hGraph = static_cast<const HierarchicalGridGraph&>(getGraph());
		return hGraph.clusterIndexToY(clusterIndex);
	}

	void HierarchicalGridGraph::Cluster::buildTopAndLeftEntrances()
	{
		buildTopEntrances();
		buildLeftEntrances();
	}

	void HierarchicalGridGraph::Cluster::buildTopEntrances()
	{
		if(getClusterY() == 0)
		{
			return;
		}

		for(UInt x = 0; x < getWidth(); x++)
		{
			EntrancePtr entrance = getMaximalLengthTopEntrance(x);

			if(entrance)
			{
				entrances.push_back(entrance);
				getGraph().getCluster(getClusterX(), getClusterY() - 1).entrances.push_back(entrance);
			}
		}
	}

	void HierarchicalGridGraph::Cluster::buildLeftEntrances()
	{
		if(getClusterX() == 0)
		{
			return;
		}

		for(UInt y = 0; y < getWidth(); y++)
		{
			EntrancePtr entrance = getMaximalLengthLeftEntrance(y);

			if(entrance)
			{
				entrances.push_back(entrance);
				getGraph().getCluster(getClusterX() - 1, getClusterY()).entrances.push_back(entrance);
			}
		}
	}

	HierarchicalGridGraph::EntrancePtr HierarchicalGridGraph::Cluster::getMaximalLengthTopEntrance(UInt& x)
	{
		const Cluster& topCluster = getGraph().getCluster(getClusterX(), getClusterY()-1);
		const UInt TOP_Y = topCluster.getHeight() - 1;

		if( !Vertex::mutuallyConnected(getVertex(x, 0), topCluster.getVertex(x, TOP_Y)) )
		{
			return EntrancePtr();
		}

		const UInt START_X = x;
		const UInt MAX_X = this->getWidth() - 1;

		while( x < MAX_X &&
			   Vertex::mutuallyConnected(getVertex(x, 0),  topCluster.getVertex(x+1, TOP_Y)) &&
			   Vertex::mutuallyConnected(getVertex(x+1, 0),  topCluster.getVertex(x, TOP_Y)) &&
			   Vertex::mutuallyConnected(getVertex(x+1, 0),  topCluster.getVertex(x+1, TOP_Y))
		     )
		{
			x++;
		}

		EntrancePtr newEntrance( new Entrance(getGraph(), START_X + getLeft(), topCluster.getBottom(), x + getLeft(), getTop()));
		return newEntrance;
	}

	HierarchicalGridGraph::EntrancePtr HierarchicalGridGraph::Cluster::getMaximalLengthLeftEntrance(UInt& y)
	{
		const Cluster& leftCluster = getGraph().getCluster(getClusterX() - 1, getClusterY());
		const UInt LEFT_X = leftCluster.getWidth() - 1;

		if( !Vertex::mutuallyConnected(getVertex(0, y), leftCluster.getVertex(LEFT_X, y)) )
		{
			return EntrancePtr();
		}

		const UInt START_Y = y;
		const UInt MAX_Y = this->getHeight() - 1;

		while( y < MAX_Y &&
			   Vertex::mutuallyConnected(getVertex(0, y),  leftCluster.getVertex(LEFT_X, y+1)) &&
			   Vertex::mutuallyConnected(getVertex(0, y+1),  leftCluster.getVertex(LEFT_X, y)) &&
			   Vertex::mutuallyConnected(getVertex(0, y+1),  leftCluster.getVertex(LEFT_X, y+1))
			 )
		{
			y++;
		}

		EntrancePtr newEntrance( new Entrance(getGraph(), leftCluster.getRight(), START_Y + getTop(), getLeft(), y + getTop()));
		return newEntrance;
	}

	UInt HierarchicalGridGraph::Cluster::getNrOfEntrances() const
	{
		return entrances.size();
	}

	HierarchicalGridGraph::Entrance& HierarchicalGridGraph::Cluster::getEntrance(const UInt& index)
	{
		return *entrances.at(index);
	}

	const HierarchicalGridGraph::Entrance& HierarchicalGridGraph::Cluster::getEntrance(const UInt& index) const
	{
		return *entrances.at(index);
	}
}//graphs

