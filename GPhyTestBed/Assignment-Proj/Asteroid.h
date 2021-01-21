/********************************************

	FILENAME -> Asteroid.H

	Course : TGD2251 Game Physics
	Session: Trimester 2, 2020/21

	ID and Name #1 : 1171100974 Yee Cui Ying
	Contacts #1 : 010-225 9059 1171100974@student.mmu.edu.my

	ID and Name #2 : 1171100663 Muhammad Syafeeq bin Mohd Fauzi
	Contacts #2 : 011-23042570 1171100663@student.mmu.edu.my

********************************************/


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
		Asteroid(b2World& world, float radius, sf::Vector2f position, sf::Color color, int thickness, sf::Color outline, sf::Texture* texture);
		void setFillColor(sf::Color col);
		void setOutlineThickness(float thickness);
		void setOutlineColor(sf::Color col);
		
		void setTexture(sf::Texture* textures);
		void update();
		b2Body* getBody();
		b2FixtureDef getBodyFix();

		sf::Shape& getShape();
		void moveForward();
};

#endif