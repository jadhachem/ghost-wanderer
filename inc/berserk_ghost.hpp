/**
 * Copyright (C) 2014 Jad Hachem <jad.hachem@gmail.com>
 * 
 * This file is part of Ghost Wanderer.
 * 
 * Ghost Wanderer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Ghost Wanderer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
