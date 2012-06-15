#ifndef GRID_GRAPH_HPP
#define GRID_GRAPH_HPP

#include "Graph.hpp"
#include "GridVertex.hpp"

#include <boost/shared_ptr.hpp>
#include <vector>

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class GridVertex;

	template <typename precision>
	class GridGraph: public Graph<precision>
	{
		public:
			typedef boost::shared_ptr<GridVertex<precision> > VertexPtr;

			GridGraph( const unsigned int& width, const unsigned int& height );

			virtual GridVertex<precision>& getVertex(const unsigned int& index);
			virtual const GridVertex<precision>& getVertex(const unsigned int& index) const;

			GridVertex<precision>& getVertex(const unsigned int& x, const unsigned int& y);
			const GridVertex<precision>& getVertex(const unsigned int& x, const unsigned int& y) const;

			unsigned int getWidth() const;
			unsigned int getHeight() const;

		protected:
			std::size_t positionToIndex(const unsigned int& x, const unsigned int& y) const;
			unsigned int indexToX(const std::size_t& index) const;
			unsigned int indexToY(const std::size_t& index) const;

			virtual void initializeVertices();
			virtual void initializeGridVertices();

			virtual void initializeEdges();

		private:
			unsigned int width, height;
	};
} //graphs
} //extern C++

#include "GridGraph.hpp"

#endif /* GRID_GRAPH_HPP */


