#ifndef GRID_GRAPH_HPP
#define GRID_GRAPH_HPP

#include "Graph.hpp"
#include "GridVertex.hpp"
#include "VertexRectangle.hpp"

#include <boost/shared_ptr.hpp>
#include <vector>

extern "C++"
{
namespace graphs
{
	class GridGraph: public Graph, VertexRectangle
	{
		public:
			GridGraph( const UInt &width, const UInt &height );
			GridGraph( const GridGraph &otherGraph, bool copyEdges = true );

			GridVertex& getVertex(const UInt &index);
			const GridVertex& getVertex(const UInt &index) const;

			virtual GridVertex& getVertex(const UInt &x, const UInt &y);
			virtual const GridVertex& getVertex(const UInt &x, const UInt &y) const;

			virtual UInt getWidth() const;
			virtual UInt getHeight() const;

			UInt positionToIndex(const UInt &x, const UInt &y) const;
			UInt indexToX(const UInt &index) const;
			UInt indexToY(const UInt &index) const;

		protected:
			class GridVertexPromotion: public VertexPromoteFunction
			{
				virtual void operator() (VertexPtr &vertex) const;
			};

		private:
			void initializeEdges();

			UInt width, height;
	};
} //graphs
} //extern C++

#endif /* GRID_GRAPH_HPP */


