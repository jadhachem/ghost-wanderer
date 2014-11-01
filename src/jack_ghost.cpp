#include "ghost.hpp"
#include "jack_ghost.hpp"
#include <SFML/Graphics.hpp>

JackGhost::JackGhost() : Ghost() {
	setColor( sf::Color::Cyan );
	bounces = false;
}

BumpEvent JackGhost::bumpEvent() {
	return BumpEvent::CLEAR;
}

