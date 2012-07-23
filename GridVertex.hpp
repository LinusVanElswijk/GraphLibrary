#ifndef GRID_VERTEX_HPP
#define GRID_VERTEX_HPP

#include "Vertex.hpp"
#include "GridGraph.hpp"

extern "C++"
{
namespace graphs
{
	class GridGraph;

	class GridVertex: public Vertex
	{
		public:
			UInt getX() const;
			UInt getY() const;

			GridGraph& getGraph();
			const GridGraph& getGraph() const;

		protected:
			GridVertex(Vertex& vertex, const UInt &x, const UInt &y);
			GridVertex(GridVertex& gridVertex);

		private:
			const UInt x,  y;

		friend class GridGraph;
	};
} //graphs
} //extern C++

#endif /* GRID_VERTEX_HPP */


