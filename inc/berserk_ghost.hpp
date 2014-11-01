#ifndef _BERSERK_GHOST_HPP_
#define _BERSERK_GHOST_HPP_

#include "red_ghost.hpp"
#include <SFML/Graphics.hpp>

class BerserkGhost : public Ghost {

	private:
		Ghost* main_ghost;
		
		sf::Clock berserk_clock;

		int timeout_ms;
		float min_speed;

		float norm(sf::Vector2f v);

	public:
		BerserkGhost(Ghost* main_ghost, int timeout, float min_v);
		virtual void move(float xmax, float ymax);
		virtual BumpEvent bumpEvent();
		virtual sf::Sprite getSprite();
		virtual void setVelocity(float vx, float vy);

};


#endif // _BERSERK_GHOST_HPP_
