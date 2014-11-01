#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "ghost.hpp"

sf::Texture Ghost::ghost_texture_1;
sf::Texture Ghost::ghost_texture_2;
sf::Clock Ghost::clock;
const float Ghost::nx = 50, Ghost::ny = 50;

Ghost::Ghost() {
	static bool textures_created = false;
	if(!textures_created) {
		int ntxtr = 0;
		if( !ghost_texture_1.loadFromFile( "data/img/ghost1.png" ) )
			std::cerr << "Could not load ghost texture" << std::endl;
		else
			ntxtr++;
		if( !ghost_texture_2.loadFromFile( "data/img/ghost2.png" ) )
			std::cerr << "Could not load ghost texture" << std::endl;
		else
			ntxtr++;

		if(ntxtr==2)
			textures_created = true;
	}
	sprite.setTexture(ghost_texture_1);
	sprite.setOrigin(nx/2,ny/2);
	mirrored = false;
	entered = false;
	bounces = true;
}
Ghost::~Ghost() {
}

void Ghost::mirror() {
	sprite.scale(-1.0f,1.0f);
	mirrored = !mirrored;
}

void Ghost::setVelocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}

void Ghost::setPosition(float x, float y) {
	sprite.setPosition(x,y);
}

void Ghost::updateOrientation() {
	if( (velocity.x<0 && !mirrored) || (velocity.x>0 && mirrored) )
		mirror();
}

sf::Sprite Ghost::getSprite() {
	sf::Time elapsed = clock.getElapsedTime();
	if(elapsed.asMilliseconds() % 1000 < 500)
		sprite.setTexture(ghost_texture_1);
	else
		sprite.setTexture(ghost_texture_2);
	return sprite;
}

float Ghost::getSpeed() {
	return std::sqrt( velocity.x*velocity.x + velocity.y*velocity.y );
}

sf::Vector2f Ghost::getVelocity() {
	return velocity;
}
sf::Vector2f Ghost::getPosition() {
	return sprite.getPosition();
}

void Ghost::setBounce(bool b) {
	bounces = b;
}

void Ghost::changeSpeed(float deltav) {
	float curr = getSpeed();
	velocity.x *= (curr+deltav)/curr;
	velocity.y *= (curr+deltav)/curr;
}

void Ghost::changeVelocity(float deltax, float deltay) {
	velocity.x += deltax;
	velocity.y += deltay;
	updateOrientation();
}

void Ghost::move(float xmax, float ymax) {
	sf::Vector2f position = sprite.getPosition();
	position += velocity;
	float left  = position.x-nx/2;
	float right = position.x+nx/2;
	float up    = position.y-ny/2;
	float down  = position.y+ny/2;
	if(entered && bounces) {
		if(left<0) {
			position.x += 2*(0.0f-left);
			velocity.x *= -1.0f;
		}
		else if(right>xmax) {
			position.x += 2*(xmax-right);
			velocity.x *= -1.0f;
		}
		if(up<0) {
			position.y += 2*(0.0f-up);
			velocity.y *= -1.0f;
		}
		else if(down>ymax) {
			position.y += 2*(ymax-down);
			velocity.y *= -1.0f;
		}
	}
	else {
		if(left>=0 && right<xmax && up>=0 && down<ymax)
			entered = true;
	}
	sprite.setPosition(position);
	updateOrientation();
}

bool Ghost::isOutside(float xmax, float ymax) {
	if(!entered)
		return false;
	sf::Vector2f position = sprite.getPosition();
	float wx = nx/2, wy = ny/2;
	float left  = position.x-wx;
	float right = position.x+wx;
	float up    = position.y-wy;
	float down  = position.y+wy;
	return (right<0 || left>=xmax || down<0 || up>=ymax);
}

bool Ghost::bump(Ghost* other) {
	float x1 = sprite.getPosition().x;
	float y1 = sprite.getPosition().y;
	float x2 = other->sprite.getPosition().x;
	float y2 = other->sprite.getPosition().y;

	float dx = x1-x2;
	float dy = y1-y2;
	float d = std::sqrt( dx*dx+dy*dy );

	return ( d < nx-15 );
}

void Ghost::setColor(sf::Color color) {
	sprite.setColor(color);
}

BumpEvent Ghost::bumpEvent() {
	return BumpEvent::NONE;
}


