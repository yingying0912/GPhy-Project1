#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player{

		private:
		sf::RectangleShape myPlayer;
		b2Body* bodyPlayer;
		b2BodyDef bodyDefPlayer;
		b2PolygonShape bodyShapePlayer;
		b2FixtureDef bodyFixtureDefPlayer;

	public:
		Player(b2World& world, sf::Vector2f size, sf::Vector2f position,
			float rotation);

		void setFillColor(sf::Color col);
		void setOutlineThickness(float thickness);
		void setOutlineColor(sf::Color col);

		void setTexture(sf::Texture* textures);

		void update();
		sf::Shape& getShape();
};

#endif