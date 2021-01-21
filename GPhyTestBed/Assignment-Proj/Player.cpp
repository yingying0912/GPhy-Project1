/********************************************

	FILENAME -> Player.CPP

	Course : TGD2251 Game Physics
	Session: Trimester 2, 2020/21

	ID and Name #1 : 1171100974 Yee Cui Ying
	Contacts #1 : 010-225 9059 1171100974@student.mmu.edu.my

	ID and Name #2 : 1171100663 Muhammad Syafeeq bin Mohd Fauzi
	Contacts #2 : 011-23042570 1171100663@student.mmu.edu.my

********************************************/



#include "Player.h"
#include "Asteroid.h"
#include <iostream>

using namespace std;

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
// Why? Refer to Computer Graphics
static const float PIXEL_PER_METER = 32.0f;

Player::Player(b2World& world, sf::Vector2f size, sf::Vector2f position,
	float rotation, sf::Color color, int thickness, sf::Color outline, sf::Texture* texture)
{
	// Set Loc and Position
	myPlayer = sf::RectangleShape(size);
	myPlayer.setOrigin(sf::Vector2f(size.x / 2, size.y));
	bodyDefPlayer.position = b2Vec2(
		position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER
	);
	bodyDefPlayer.type = b2_dynamicBody;

	myPlayer.setFillColor(color);
	myPlayer.setOutlineThickness(thickness);
	myPlayer.setOutlineColor(outline);

	myPlayer.setTexture(texture);

	bodyShapePlayer.SetAsBox((size.x / 2) / PIXEL_PER_METER, (size.y / 2) / PIXEL_PER_METER);

	bodyFixtureDefPlayer.shape = &bodyShapePlayer;
	bodyFixtureDefPlayer.density = .3f;
	bodyFixtureDefPlayer.friction = .5f;

	bodyPlayer = world.CreateBody(&bodyDefPlayer);
	bodyPlayer->CreateFixture(&bodyFixtureDefPlayer);
	
	bodyPlayer->SetGravityScale(0);

	health = 10;
	currentHealth = health;
}

void Player::update()
{
	// Box2D uses radians for rotation, SFML uses degree
	myPlayer.setRotation(bodyPlayer->GetAngle() * 180 / b2_pi);
	myPlayer.setPosition(bodyPlayer->GetPosition().x*PIXEL_PER_METER, bodyPlayer->GetPosition().y*PIXEL_PER_METER);

}

void Player::update(float windowX, float windowY)
{
	// Checking Breaking Wall
	sf::Vector2f playerData = this->getShape().getPosition();
	if (playerData.y < 0) {
		bodyPlayer->ApplyForce(b2Vec2(0, 1), bodyPlayer->GetWorldCenter(), true);
	}
	if (playerData.y > windowY) {
		bodyPlayer->ApplyForce(b2Vec2(0, -1), bodyPlayer->GetWorldCenter(), true);
	}
	if (playerData.x > windowX) {
		bodyPlayer->ApplyForce(b2Vec2(-1, 0), bodyPlayer->GetWorldCenter(), true);
	}
	if (playerData.x < 0) { 
		bodyPlayer->ApplyForce(b2Vec2(1, 0), bodyPlayer->GetWorldCenter(), true);
	}
}

void Player::update(b2Vec2 force){
	bodyPlayer->ApplyForce(force, bodyPlayer->GetWorldCenter(), true);
}

void Player::setFillColor(sf::Color col)
{
	myPlayer.setFillColor(col);
}

void Player::setOutlineThickness(float thickness)
{
	myPlayer.setOutlineThickness(thickness);
}

void Player::setOutlineColor(sf::Color col)
{
	myPlayer.setOutlineColor(col);
}

void Player::setTexture(sf::Texture* textures)
{
	myPlayer.setTexture(textures, true);
}

sf::Shape& Player::getShape()
{
	// TODO: insert return statement here
	return myPlayer;
}

void Player::damaged(){
	currentHealth--;
}

void Player::reset(float x, float y){
	//myPlayer.setPosition(x, y);
	bodyDefPlayer.position = b2Vec2(
		25 / PIXEL_PER_METER, 25 / PIXEL_PER_METER
	);
	bodyPlayer->ApplyForce(b2Vec2(0,0), bodyPlayer->GetWorldCenter(), true);
	bodyPlayer->SetLinearVelocity(b2Vec2(0, 0));
	bodyPlayer->SetAngularVelocity(0);
	bodyPlayer->SetFixedRotation(true);
}

void Player::reset(sf::Vector2f position) {
	bodyPlayer->SetTransform(b2Vec2(position.x, position.y), 180.f);
	bodyPlayer->ApplyForce(b2Vec2(0, 0), bodyPlayer->GetWorldCenter(), true);
}

int Player::getCurrentHealth(){
	return currentHealth;
}