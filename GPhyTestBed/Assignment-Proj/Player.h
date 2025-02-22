/********************************************

	FILENAME -> Player.H

	Course : TGD2251 Game Physics
	Session: Trimester 2, 2020/21

	ID and Name #1 : 1171100974 Yee Cui Ying
	Contacts #1 : 010-225 9059 1171100974@student.mmu.edu.my

	ID and Name #2 : 1171100663 Muhammad Syafeeq bin Mohd Fauzi
	Contacts #2 : 011-23042570 1171100663@student.mmu.edu.my

********************************************/

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
		int health;
		int currentHealth;

	public:
		Player(b2World& world, sf::Vector2f size, sf::Vector2f position,
			float rotation, sf::Color color, int thickness, sf::Color outline, sf::Texture* texture);

		void setFillColor(sf::Color col);
		void setOutlineThickness(float thickness);
		void setOutlineColor(sf::Color col);

		void setTexture(sf::Texture* textures);
		void rotate(float angle);

		void update(float windowX, float windowY);
		void update();
		void update(b2Vec2 force);

		void damaged();
		void reset(float x, float y);
		void reset(sf::Vector2f position);

		int getCurrentHealth();

		sf::Shape& getShape();
};

#endif