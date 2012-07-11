#ifndef GRID_VERTEX_HPP
#define GRID_VERTEX_HPP

#include "Vertex.hpp"
#include "GridGraph.hpp"

extern "C++"
{
namespace graphs
{
	template <typename precision>
	class GridGraph;

	template <typename precision>
	class GridVertex: public Vertex<precision>
	{
		public:
			unsigned int getX() const;
			unsigned int getY() const;

			virtual GridGraph<precision>& getGraph();
			virtual const GridGraph<precision>& getGraph() const;

		protected:
			GridVertex(Vertex<precision>& vertex, const unsigned int& x, const unsigned int& y);
			GridVertex(GridVertex<precision>& gridVertex);

		private:
			const unsigned int x,  y;

		friend class GridGraph<precision>;
	};
} //graphs
} //extern C++

#endif /* GRID_VERTEX_HPP */


