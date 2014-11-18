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

#include <iostream>
#include "ghost.hpp"
#include "ghost_factory.hpp"
#include "random_gen.hpp"
#include <SFML/Graphics.hpp>

#include <assert.h>

void testGhostGeneration();

int main(int argc, char **argv) {

	rnd::rand_init();

	testGhostGeneration();

	return 0;
}

bool isOutside(Ghost *ghost, float nx, float ny) {
	sf::Vector2f pos = ghost->getPosition();
	return ( pos.x-25<0 || pos.x+25>=nx || pos.y-25<0 || pos.y+25>=ny );
}

void testGhostGeneration() {

	GhostFactory factory;
	factory.setArenaDimensions(100,100);
	Ghost *ghost;

	for(int i=0; i<10; i++) {
		ghost = factory.createMainGhost();
		assert( ! isOutside(ghost,100,100) );
		delete ghost;
	}
	for(int i=0; i<10; i++) {
		ghost = factory.createNewGhost();
		assert( isOutside(ghost,100,100) );
		delete ghost;
	}

}

