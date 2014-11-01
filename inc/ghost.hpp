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
