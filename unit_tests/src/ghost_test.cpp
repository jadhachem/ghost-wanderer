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
#include <SFML/Graphics.hpp>
#include <cmath>

#include <assert.h>

#define tol 1e-9

bool deq(float a, float b) {
	return std::abs(a-b)<tol;
}
bool veq(sf::Vector2f v1, sf::Vector2f v2) {
	return deq(v1.x,v2.x) && deq(v1.y,v2.y);
}
bool veq(sf::Vector2f v, float x, float y) {
	return veq(v,sf::Vector2f(x,y));
}

void test_move();
void test_outside();

int main(int argc, char **argv) {
	
	test_move();
	test_outside();

	return 0;
}

void test_outside() {
	Ghost ghost;

	ghost.setPosition(-100,100);
	assert( !ghost.isOutside(300,300) );
	ghost.setVelocity(200,0);
	ghost.move(300,300);
	assert( !ghost.isOutside(300,300) );

	ghost.setBounce(true);
	ghost.setVelocity(-150,0);
	ghost.move(300,300);
	assert( !ghost.isOutside(300,300) );
	
	ghost.setBounce(false);
	ghost.setVelocity(-150,0);
	ghost.move(300,300);
	assert( ghost.isOutside(300,300) );

	Ghost ghost2;
	ghost2.setBounce(false);
	ghost2.setPosition(-100,100);
	ghost2.setVelocity(125+tol,0);
	ghost2.move(300,300);
	assert( !ghost2.isOutside(300,300) );
	ghost2.setVelocity(-1,0);
	ghost2.move(300,300);
	assert( !ghost2.isOutside(300,300) );
	ghost2.setVelocity(-24,0);
	ghost2.move(300,300);
	assert( !ghost2.isOutside(300,300) );
	ghost2.setVelocity(-26,0);
	ghost2.move(300,300);
	assert( ghost2.isOutside(300,300) );

	ghost2.setPosition(100,100);
	ghost2.setVelocity(0,50+tol);
	ghost2.move(150,150);
	assert( !ghost2.isOutside(150,150) );
	ghost2.move(150,150);
	assert( ghost2.isOutside(150,150) );
}

void test_move() {
	Ghost ghost;
	sf::Vector2f pos;
	sf::Vector2f vel;

	ghost.setPosition(100,100);
	ghost.setVelocity(-60,0);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,40,100) );
	assert( veq(vel,-60,0) );

	ghost.setPosition(100,100);
	ghost.setVelocity(0,100);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,100,200) );
	assert( veq(vel,0,100) );

	ghost.setPosition(100,100);
	ghost.setVelocity(-20,20);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,80,120) );
	assert( veq(vel,-20,20) );

	ghost.setBounce(true);

	ghost.setPosition(100,100);
	ghost.setVelocity(-100,0);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,50,100) );
	assert( veq(vel,100,0) );

	ghost.setPosition(100,100);
	ghost.setVelocity(-150,-150);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,100,100) );
	assert( veq(vel,150,150) );

	ghost.setPosition(200,150);
	ghost.setVelocity(200,150);
	ghost.move(300,300);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,150,250) );
	assert( veq(vel,-200,-150) );

	ghost.setPosition(125,125);
	ghost.setVelocity(-100,-200);
	ghost.move(300,300);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,25,125) );
	assert( veq(vel,-100,200) );

	ghost.setBounce(false);

	ghost.setPosition(100,100);
	ghost.setVelocity(-200,0);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,-100,100) );
	assert( veq(vel,-200,0) );

	ghost.setPosition(100,100);
	ghost.setVelocity(-150,-150);
	ghost.move(500,500);
	pos = ghost.getPosition();
	vel = ghost.getVelocity();
	assert( veq(pos,-50,-50) );
	assert( veq(vel,-150,-150) );
}



