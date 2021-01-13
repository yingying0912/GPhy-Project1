#include "Player.h"
#include "MyRectangle.h"

Player::Player(b2World& world, sf::Vector2f size, sf::Vector2f position){
	player = MyRectangle(world, size, position, 0.0, false);
	player.setOutlineThickness(1);
	player.setOutlineColor(sf::Color::Black);
	player.setFillColor(sf::Color(0, 255, 0));
}

