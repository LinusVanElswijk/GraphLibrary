#ifndef VERTEX_RECTANGLE
#define VERTEX_RECTANGLE

#include "Types.hpp"

namespace graphs
{
	class VertexRectangle
	{
		public:
			virtual UInt getWidth()  const = 0;
			virtual UInt getHeight() const = 0;

			virtual UInt getTop()    const = 0;
			virtual UInt getBottom() const = 0;
			virtual UInt getLeft()   const = 0;
			virtual UInt getRight()  const = 0;

			virtual GridVertex& getVertex(const UInt &x, const UInt &y) = 0;
			virtual const GridVertex& getVertex(const UInt &x, const UInt &y) const = 0;
	};

}

#endif
