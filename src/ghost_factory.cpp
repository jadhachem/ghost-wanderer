#include <iomanip>
#include "ghost.hpp"
#include "red_ghost.hpp"
#include "jack_ghost.hpp"
#include "berserk_ghost.hpp"
#include "ghost_factory.hpp"

namespace {
	double p_jack_0 = 0.125;
	double p_jack_decrease = 0.75;
	double p_jack_increase = 1.01;

	double p_berserk = 0.025;
	int berserk_timeout = 6000;
	float min_berserk_speed = 2.5f;

	float speed_multiplier_0 = 1.0;
	float speed_multiplier_inc = 0.5;

	int initial_number_0 = 10;
	int initial_number_inc = 0;

	int ghost_period_ms = 5000;
}

GhostFactory::GhostFactory() {
	speed_mult = speed_multiplier_0;
	p_jack = p_jack_0;
	initial_number = initial_number_0;
}

void GhostFactory::setArenaDimensions(float x, float y) {
	nx = x;
	ny = y;
}

bool GhostFactory::newGhostAvailable() {
	sf::Time elapsed = ghost_clock.getElapsedTime();
	int elapsed_ms = elapsed.asMilliseconds();
	return (elapsed_ms > ghost_period_ms);
}


sf::Vector2f GhostFactory::randomVelocity() {
	int xi = rnd::bernoulli(.5)?1:-1;
	int yi = rnd::bernoulli(.5)?1:-1;
	float vx = xi * ( 0.9 * rnd::uniform() + 0.1 );
	float vy = yi * ( 0.9 * rnd::uniform() + 0.1 );
	return sf::Vector2f(vx,vy);
}

sf::Vector2f GhostFactory::randomPosition() {
	float x = 25 + (nx-50) * rnd::uniform();
	float y = 25 + (ny-50) * rnd::uniform();
	return sf::Vector2f(x,y);
}


sf::Vector2f GhostFactory::outsidePosition(
				sf::Vector2f vel, sf::Vector2f pos) {
	// x0,y0,t such that x0-t*vx=x, y0-t*vy=y
	float t_left  = (-50   - pos.x) / vel.x;
	float t_right = (nx+50 - pos.x) / vel.x;
	float t_up    = (-50   - pos.y) / vel.y;
	float t_down  = (ny+50 - pos.y) / vel.y;

	float t_hor   = (t_left<t_right)?-t_left:-t_right;
	float t_ver   = (t_up  <t_down )?-t_up:-t_down;

	float t = (t_hor<t_ver)?t_hor:t_ver;

	float x0 = pos.x - t * vel.x;
	float y0 = pos.y - t * vel.y;

	return sf::Vector2f(x0,y0);
}

sf::Vector2f GhostFactory::randomDirection() {
	float vx = rnd::bernoulli(.5)?-.5:.5;
	float vy = rnd::bernoulli(.5)?-.5:.5;
	return sf::Vector2f( vx , vy );
}

void GhostFactory::initializeGhost(Ghost* ghost, bool outside) {
	sf::Vector2f vel = speed_mult * randomVelocity();
	sf::Vector2f pos = randomPosition();
	if(outside)
		pos = outsidePosition(vel,pos);
	ghost->setPosition( pos.x, pos.y );
	ghost->setVelocity( vel.x, vel.y );
}

Ghost* GhostFactory::createMainGhost() {
	main_ghost = new Ghost();
	sf::Vector2f vel( randomDirection() );
	sf::Vector2f pos( randomPosition() );
	main_ghost->setPosition( pos.x, pos.y );
	main_ghost->setVelocity( vel.x, vel.y );
	return main_ghost;
}

Ghost* GhostFactory::createNewGhost() {
	Ghost* ghost;
	bool special = rnd::bernoulli( p_jack + p_berserk );
	if(special) {
		bool jack = rnd::bernoulli(p_jack/(p_jack+p_berserk));
		if(jack)
			ghost = new JackGhost();
		else
			ghost = new BerserkGhost(
							main_ghost,
							berserk_timeout,
							min_berserk_speed);
	}
	else
		ghost = new RedGhost();
	initializeGhost(ghost,true);
	return ghost;
}

std::list<Ghost*> GhostFactory::createGhostWave() {
	std::list<Ghost*> wave;
	for(int i=0; i<initial_number; i++) {
		Ghost* ghost = new RedGhost();
		initializeGhost(ghost,true);
		wave.push_back( ghost );
	}
	return wave;
}

void GhostFactory::resetClock() {
	ghost_clock.restart();
}

void GhostFactory::increaseJackLikelihood() {
	double newp = p_jack * p_jack_increase;
	if(newp<p_jack_0)
		p_jack = newp;
	else
		p_jack = p_jack_0;
}

void GhostFactory::nextLevel() {
	p_jack *= p_jack_decrease;
	speed_mult += speed_multiplier_inc;
	initial_number += initial_number_inc;
}

void GhostFactory::printState(std::ostream &out) {
	static bool first = true;
	if(first)
		out << "Status:" << std::endl;
	else
		out << "\033[F\033[K" << std::flush;
	out << "P(jack) = " << std::setw(11) << p_jack;
	out << " ;  Speed Mult = " << speed_mult;
	out << std::endl;
	first = false;
}


