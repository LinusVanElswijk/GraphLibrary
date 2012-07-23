/*
 * HierarchicalGridMap.cpp
 *
 *  Created on: Jan 3, 2012
 *      Author: Linus
 */

/*#include "HierarchicalGridGraph.hpp"

#include <cmath>
#include <iostream>

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
		buildClusters();

		std::cout << "now starting on entrances" << std::endl;

		buildEntrances();
	}
	/*
	template <typename precision>
	HierarchicalGridMap<precision>::~HierarchicalGridMap()
	{
		// TODO Auto-generated destructor stub
	}
	/
	UInt HierarchicalGridGraph::getNrOfClusters() const
	{
		return clusters.size();
	}

	UInt HierarchicalGridGraph::getNrOfEntrances() const
	{
		return entrances.size();
	}

	UInt HierarchicalGridGraph::getAbstractionWidth() const
	{
		return abstractionWidth;
	}

	UInt HierarchicalGridGraph::getAbstractionHeight() const
	{
		return abstractionHeight;
	}

	void HierarchicalGridGraph::buildClusters()
	{
		const unsigned int delta = clusterSize - 1;

		std::cout << "Constructing" << std::endl;

		for(unsigned int x = 0; x < this->getWidth(); x+=clusterSize)
		{
		    for(unsigned int y = 0; y < this->getHeight(); y+=clusterSize)
			{
				const unsigned int x2 = std::min(x + delta, this->getWidth()),
								   y2 = std::min(y + delta, this->getHeight());

				GridVertex& topLeft  = this->getVertex(x, y);
				GridVertex& bottomRight = this->getVertex(x2, y2);

				ClusterPtr ptr(new Cluster(topLeft, bottomRight));

				ptr->getTopRow();

				clusters.push_back(ptr);
			}
		}

		std::cout << clusters.size() << " clusters build" << std::endl;
	}

	void HierarchicalGridGraph::buildEntrances()
	{
		for(UInt x = 0; x < getAbstractionWidth(); x++)
		{
			for(UInt y = 1; y < getAbstractionHeight(); y++)
			{
				buildTopEntrances(x, y);
			}
		}

		for(UInt x = 1; x < getAbstractionWidth(); x++)
		{
			for(UInt y = 0; y < getAbstractionHeight(); y++)
			{
				//buildLeftEntrances(x, y);
			}
		}

		std::cout << entrances.size() << " entrances build" << std::endl;
	}

	void HierarchicalGridGraph::buildTopEntrances(const UInt& clusterX, const UInt& clusterY)
	{
		ClusterPtr current = clusters.at(positionToClusterIndex(clusterX, clusterY)),
				   above   = clusters.at(positionToClusterIndex(clusterX, clusterY-1));

		const UInt START_X  = current->left,
				   END_X    = current->right;

		std::vector<GridVertex&> topRow = above->getBottomRow(),
				                 bottomRow = current->getTopRow();

		for(UInt x = 0; x < topRow.size(); x++)
		{
			EntrancePtr entrance = getMaximalLengthEntrance(topRow, bottomRow, x, END_X);

			if(entrance)
			{
				entrances.push_back(entrance);
			}
		}
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// class Entrance

	HierarchicalGridGraph::Entrance::Entrance(GridVertex &vertexA, GridVertex &vertexB)
	:Rectangle(vertexA, vertexB)
	{

	}
	/
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


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// class Cluster

	HierarchicalGridGraph::Cluster::Cluster(GridVertex& vertexA, GridVertex& vertexB)
	:Rectangle(vertexA, vertexB),
	 entrances()
	{

	}

	/
	template <typename precision>
	void HierarchicalGridMap<precision>::Cluster::getTopRow()
	{
		const unsigned int maxX = bottomRight.getX(),
						   y	= topLeft.getY();

		std::list<Vertex&> row = std::list<Vertex&>();

		for(unsigned int x = topLeft.getX(); x <= maxX; x++)
		{
			row.push_back(map.getVertex(x, y));
		}

		//return row;
	}
	/
}//graphs
*/
