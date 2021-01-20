/********************************************

	FILENAME -> MyRectangle.H

	Course : TGD2251 Game Physics
	Session: Trimester 2, 2020/21

	ID and Name #1 : 1171100974 Yee Cui Ying
	Contacts #1 : 010-225 9059 EMailOfStud1

	ID and Name #2 : 1171100663 Muhammad Syafeeq bin Mohd Fauzi
	Contacts #2 : 011-23042570 fauzisyafeeq@gmail.com

********************************************/



#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class MyRectangle
{
	 private:
		sf::RectangleShape rect_;
		b2Body* body_;
		b2BodyDef bodyDef_;
		b2PolygonShape bodyShape_;
		b2FixtureDef bodyFixtureDef_;

	 public:
		MyRectangle(b2World& world,
				   sf::Vector2f size,
						sf::Vector2f position,
						float rotation = 0,
				   bool isDynamic = true
				  );
		MyRectangle();
		void setFillColor(sf::Color col);
		void setOutlineThickness(float thickness);
		void setOutlineColor(sf::Color col);
		void update();
		sf::Shape& getShape();
};

#endif