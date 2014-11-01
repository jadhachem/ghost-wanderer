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

#ifndef _GHOST_FACTORY_HPP_
#define _GHOST_FACTORY_HPP_

#include <ostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "ghost.hpp"
#include "random_gen.hpp"


class GhostFactory {

	private:
		float nx, ny;
		float speed_mult;
		double p_jack;
		int initial_number;

		Ghost* main_ghost;

		sf::Clock ghost_clock;

		sf::Vector2f randomVelocity();
		sf::Vector2f randomPosition();
		sf::Vector2f outsidePosition(
							sf::Vector2f vel, sf::Vector2f pos );
		sf::Vector2f randomDirection();

		//Ghost generateGhost(bool outside = false);
		void initializeGhost(Ghost* ghost, bool outside);
	
	public:
		GhostFactory();
		void setArenaDimensions(float x, float y);

		Ghost* createMainGhost();
		Ghost* createNewGhost();
		std::list<Ghost*> createGhostWave();
		bool newGhostAvailable();

		void resetClock();
		void increaseJackLikelihood();
		void nextLevel();

		void printState(std::ostream &out);
};


#endif // _GHOST_FACTORY_HPP_
