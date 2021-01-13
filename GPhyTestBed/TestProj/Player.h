#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "MyRectangle.h"

struct Player{
public:
	MyRectangle player;
	Player(b2World& world, sf::Vector2f size, sf::Vector2f position);
};

#endif