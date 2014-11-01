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
