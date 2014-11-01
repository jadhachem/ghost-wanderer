#include <iostream>
#include <cmath>
#include "berserk_ghost.hpp"

namespace {
//	float extra_speed = 1.5f;
//	float speed_mult = 3.0f;
}

BerserkGhost::BerserkGhost(Ghost* main_g, int timeout, float min_v) : Ghost() {
	main_ghost = main_g;
	setColor( sf::Color::Yellow );
	bounces = true;
	timeout_ms = timeout;
	min_speed = min_v;
}

BumpEvent BerserkGhost::bumpEvent() {
	return BumpEvent::LOSE;
}

float BerserkGhost::norm(sf::Vector2f v) {
	return std::sqrt( v.x*v.x + v.y*v.y );
}

void BerserkGhost::setVelocity(float vx, float vy) {
	Ghost::setVelocity(vx,vy);
//	velocity *= ( norm(velocity) + extra_speed ) / norm(velocity);
	float v = norm(velocity);
	if(v<min_speed)
		velocity *= min_speed / v;
}

void BerserkGhost::move(float xmax, float ymax) {

	int elapsed = berserk_clock.getElapsedTime().asMilliseconds();
	if( elapsed < timeout_ms ) {

		sf::Vector2f curr_pos = getPosition();
		sf::Vector2f main_pos = main_ghost->getPosition();

		sf::Vector2f disp = main_pos - curr_pos;
		
		sf::Vector2f v_dir = velocity / norm(velocity);
		sf::Vector2f d_dir = disp / norm(disp);
		sf::Vector2f new_dir = ( 4.0f*v_dir + d_dir );

		velocity = new_dir / norm(new_dir) * norm(velocity);

	}
	else {
		bounces = false;
	}
	Ghost::move(xmax,ymax);

}

sf::Sprite BerserkGhost::getSprite() {
	if( clock.getElapsedTime().asMilliseconds() % 200 < 100)
		setColor( sf::Color::Yellow );
	else
		setColor( sf::Color::Blue );
	return Ghost::getSprite();
}


