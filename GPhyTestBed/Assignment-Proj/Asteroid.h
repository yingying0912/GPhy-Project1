#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Asteroid
{
	private:
		sf::CircleShape circle_;
		b2Body* body_;
		b2BodyDef bodyDef_;
		b2CircleShape bodyShape_;
		b2FixtureDef bodyFixtureDef_;

	public:
		Asteroid(b2World& world, float radius, sf::Vector2f position);

		void setFillColor(sf::Color col);
		void setOutlineThickness(float thickness);
		void setOutlineColor(sf::Color col);
		
		void setTexture(sf::Texture* textures);

		void update();
		sf::Shape& getShape();
};

#endif