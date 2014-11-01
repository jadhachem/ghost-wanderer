#ifndef _RED_GHOST_HPP_
#define _RED_GHOST_HPP_

#include "ghost.hpp"

class RedGhost: public Ghost {

	public:
		RedGhost();
		virtual BumpEvent bumpEvent();
};


#endif // _RED_GHOST_HPP_

