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
			typedef typename Graph<precision>::VertexIndex VertexIndex;
			typedef boost::shared_ptr<GridVertex<precision> > VertexPtr;

			GridGraph( const VertexIndex& width, const VertexIndex& height );

			virtual GridVertex<precision>& getVertex(const VertexIndex& index);
			virtual const GridVertex<precision>& getVertex(const VertexIndex& index) const;

			GridVertex<precision>& getVertex(const VertexIndex& x, const VertexIndex& y);
			const GridVertex<precision>& getVertex(const VertexIndex& x, const VertexIndex& y) const;

			VertexIndex getWidth() const;
			VertexIndex getHeight() const;

			VertexIndex positionToIndex(const VertexIndex& x, const VertexIndex& y) const;
			VertexIndex indexToX(const VertexIndex& index) const;
			VertexIndex indexToY(const VertexIndex& index) const;

		protected:

			virtual void initializeVertices();
			virtual void initializeGridVertices();

			virtual void initializeEdges();

		private:
			VertexIndex width, height;
	};
} //graphs
} //extern C++

#include "GridGraph.hpp"

#endif /* GRID_GRAPH_HPP */


