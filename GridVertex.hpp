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

			GridGraph<precision>& getGraph();
			const GridGraph<precision>& getGraph() const;

		protected:
			GridVertex(GridGraph<precision>& graph, const unsigned int& x, const unsigned int& y);

		private:
			const unsigned int x,  y;

		friend class GridGraph<precision>;
	};
} //graphs
} //extern C++

#endif /* GRID_VERTEX_HPP */


