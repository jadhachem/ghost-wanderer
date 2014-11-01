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

#ifndef _GHOST_HPP_
#define _GHOST_HPP_

#include <SFML/Graphics.hpp>

enum class BumpEvent {
	NONE,
	LOSE,
	CLEAR
};

class Ghost {

	private:
		static sf::Texture ghost_texture_1;
		static sf::Texture ghost_texture_2;
		static const float nx,ny;

	protected:
		static sf::Clock clock;

		bool bounces;
		bool entered;
		bool mirrored;
		void updateOrientation();
		void mirror();

		sf::Sprite sprite;
		sf::Vector2f velocity;
		
	public:
		Ghost();
		virtual ~Ghost();

		virtual sf::Sprite getSprite();
		void setColor(sf::Color color);

		virtual void setPosition(float x, float y);
		virtual void setVelocity(float vx, float vy);
		void changeVelocity(float deltax, float deltay);
		void changeSpeed(float deltav);

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();

		bool bump(Ghost* other);
		bool isOutside(float xmax, float ymax);
		void setBounce(bool b);
		
		virtual void move(float xmax, float ymax);
		virtual BumpEvent bumpEvent();
};


#endif // _GHOST_HPP_
