#include <iostream>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "ghost.hpp"
#include "random_gen.hpp"
#include "ghost_factory.hpp"

namespace {
	const std::string VERSION = "Ghost Wanderer v0.0.3";
}

void printSeconds(sf::Time time) {
	int seconds = static_cast<int>( time.asSeconds() );
	int h = seconds / 3600;
	int m = ( seconds % 3600 ) / 60;
	int s = seconds % 60;
	
	if(h>0)
		std::cout << h << "h ";
	if(h>0 || m>0)
		std::cout << m << "m ";
	std::cout << s << "s" << std::endl;
}

void printScore(sf::Clock score_clock) {
	std::cout << "Game over!" << std::endl;
	std::cout << "Your score: ";
	sf::Time time = score_clock.getElapsedTime();
	printSeconds(time);
}


int main() {
	std::cout << VERSION << std::endl;

	rnd::rand_init();

	float nx = 700;
	float ny = 700;

	GhostFactory factory;
	factory.setArenaDimensions(nx,ny);

	bool empty = true;

	sf::RenderWindow window(sf::VideoMode(nx,ny), VERSION);

	Ghost* ghost = factory.createMainGhost();
	std::list<Ghost*> others;

	sf::Clock score_clock;
	factory.printState(std::cout);

	while(window.isOpen()) {

		sf::sleep( sf::milliseconds(10) );

		if( factory.newGhostAvailable() ) {

			factory.resetClock();
			if(empty) {
				std::list<Ghost*> wave = factory.createGhostWave();
				others.insert( others.end(), wave.begin(), wave.end() );
				empty = false;
			}
			else {
				others.push_back( factory.createNewGhost() );
				factory.increaseJackLikelihood();
			}
			factory.printState(std::cout);

		}

		sf::Event event;
		while(window.pollEvent(event)) {
		
			switch(event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					switch(event.key.code) {
						case sf::Keyboard::Left:
							ghost->changeVelocity(-1,0);
							break;
						case sf::Keyboard::Right:
							ghost->changeVelocity(1,0);
							break;
						case sf::Keyboard::Up:
							ghost->changeVelocity(0,-1);
							break;
						case sf::Keyboard::Down:
							ghost->changeVelocity(0,1);
							break;
						default:
							break;
					}

				default:
					break;
			}
		}

		window.clear(sf::Color(100,100,100));

		ghost->move(nx,ny);

		std::list<Ghost*>::iterator it = others.begin();
		while( !others.empty() && it!=others.end() ) {
			Ghost* other = (*it);
			other->move(nx,ny);
			if( other->bump(ghost) ) {
				BumpEvent bump = other->bumpEvent();
				switch(bump) {

					case BumpEvent::LOSE:
						while(!others.empty()) {
							delete others.front();
							others.pop_front();
						}
						window.close();
						break;

					case BumpEvent::CLEAR:
						while(!others.empty()) {
							delete others.front();
							others.pop_front();
						}
						empty = true;
						factory.resetClock();
						factory.nextLevel();
						factory.printState(std::cout);
						break;

					default:
						break;
				}
			}
			if( other->isOutside(nx,ny) ) {
				delete other;
				it = others.erase(it);
			}
			else
				it++;
		}
		for(it=others.begin(); it!=others.end(); it++)
			window.draw((*it)->getSprite());

		window.draw(ghost->getSprite());

		window.display();

	}

	printScore(score_clock);
	delete ghost;

	return 0;
}



