#include "ghost.hpp"
#include "red_ghost.hpp"
#include <SFML/Graphics.hpp>

RedGhost::RedGhost() : Ghost() {
	setColor( sf::Color::Magenta );
	bounces = true;
}

BumpEvent RedGhost::bumpEvent() {
	return BumpEvent::LOSE;
}



