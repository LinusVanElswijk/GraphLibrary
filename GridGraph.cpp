#include <iostream>
#include <cmath>
#include "GridGraph.hpp"

namespace graphs
{
	template<typename precision>
	GridGraph<precision>::GridGraph( const unsigned int& width, const unsigned int& height )
    :Graph<precision>(width*height),
	 width(width),
     height(height)
	{
		initializeGridVertices();
		initializeEdges();
	}

	template<typename precision>
	GridVertex<precision>& GridGraph<precision>::getVertex(const unsigned int& index)
	{
		Vertex<precision>& vertex = Graph<precision>::getVertex(index);
		return static_cast<GridVertex<precision>& >(vertex);
	}

	template<typename precision>
	const GridVertex<precision>& GridGraph<precision>::getVertex(const unsigned int& index) const
	{
		const Vertex<precision>& vertex = Graph<precision>::getVertex(index);
		return static_cast<const GridVertex<precision>& >(vertex);
	}

	template<typename precision>
	GridVertex<precision>& GridGraph<precision>::getVertex(const unsigned int& x, const unsigned int& y)
	{
		return getVertex( positionToIndex(x, y) );
	}

	template<typename precision>
	const GridVertex<precision>& GridGraph<precision>::getVertex(const unsigned int& x, const unsigned int& y) const
	{
		return getVertex( positionToIndex(x, y) );
	}

	template<typename precision>
	unsigned int GridGraph<precision>::getWidth() const
	{
		return width;
	}

	template<typename precision>
	unsigned int GridGraph<precision>::getHeight() const
	{
		return height;
	}

	template<typename precision>
	void GridGraph<precision>::initializeVertices()
	{
		const std::size_t NR_OF_VERTICES = this->getNrOfVertices();
		this->vertices.reserve(NR_OF_VERTICES);
	}

	template<typename precision>
	void GridGraph<precision>::initializeGridVertices()
	{
		const unsigned int NR_OF_VERTICES = width*height;

		for(std::size_t i = 0; i < NR_OF_VERTICES; i++)
		{
			const unsigned int X = indexToX(i),
							   Y = indexToY(i);

			VertexPtr vertexPtr(new GridVertex<precision>(*this, X, Y));

			this->vertices.push_back( vertexPtr );
		}
	}

	template<typename precision>
	void GridGraph<precision>::initializeEdges()
	{
		const precision SQRT_2 = (precision)std::sqrt(2.0);

		for(unsigned int x = 1; x < width; x++)
		{
			for(unsigned int y = 1; y < height; y++)
			{
				this->addBidirectionalEdge(this->getVertex(x, y), this->getVertex(x-1, y), (precision)1.0);
				this->addBidirectionalEdge(this->getVertex(x, y), this->getVertex(x, y-1), (precision)1.0);
				this->addBidirectionalEdge(this->getVertex(x, y), this->getVertex(x-1, y-1), (precision)SQRT_2);
				this->addBidirectionalEdge(this->getVertex(x-1, y), this->getVertex(x, y-1), (precision)SQRT_2);
			}
		}

		for(unsigned int x = 1; x < width; x++)
		{
			this->addBidirectionalEdge(this->getVertex(x,0), this->getVertex(x-1, 0), (precision)1.0);
		}

		for(unsigned int y = 1; y < height; y++)
		{
			this->addBidirectionalEdge(this->getVertex(0,y), this->getVertex(0, y-1), (precision)1.0);
		}
	}

	template<typename precision>
	std::size_t GridGraph<precision>::positionToIndex(const unsigned int& x, const unsigned int& y) const
	{
		return std::size_t(x + y * (width));
	}

	template<typename precision>
	unsigned int GridGraph<precision>::indexToX(const std::size_t& index) const
	{
		return index % (width);
	}

	template <typename precision>
	unsigned int GridGraph<precision>::indexToY(const std::size_t& index) const
	{
		return index / (width);
	}

	template class GridGraph<float>;
	template class GridGraph<double>;
}//graphs
