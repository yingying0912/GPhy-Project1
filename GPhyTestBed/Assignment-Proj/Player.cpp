#include "Player.h"
#include <iostream>

using namespace std;

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
// Why? Refer to Computer Graphics
static const float PIXEL_PER_METER = 32.0f;

Player::Player(b2World& world, sf::Vector2f size, sf::Vector2f position,
	float rotation)
{
	// Set Loc and Position
	myPlayer = sf::RectangleShape(size);
	myPlayer.setOrigin(sf::Vector2f(size.x / 2, size.y));
	bodyDefPlayer.position = b2Vec2(
		position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER
	);
	bodyDefPlayer.type = b2_dynamicBody;

	myPlayer.setFillColor(sf::Color(255, 255, 255, 255));
	myPlayer.setOutlineThickness(1);
	myPlayer.setOutlineColor(sf::Color::Black);

	bodyShapePlayer.SetAsBox((size.x / 2) / PIXEL_PER_METER, (size.y / 2) / PIXEL_PER_METER);

	bodyFixtureDefPlayer.shape = &bodyShapePlayer;
	bodyFixtureDefPlayer.density = .3f;
	bodyFixtureDefPlayer.friction = .5f;

	bodyPlayer = world.CreateBody(&bodyDefPlayer);
	bodyPlayer->CreateFixture(&bodyFixtureDefPlayer);
	
	bodyPlayer->SetGravityScale(0.5);
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		cout << "Key " << sf::Keyboard::Space << ": Space is Pressed." << endl
			<< " Booster Launched! " << endl;
		bodyPlayer->ApplyForce(b2Vec2(0, -2), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		cout << "Key " << sf::Keyboard::A << ": A is Pressed." << endl
			<< " Going Left " << endl;
		bodyPlayer->ApplyForce(b2Vec2(-1.5, 0), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		cout << "Key " << sf::Keyboard::D << ": D is Pressed." << endl
			<< " Going Right " << endl;
		bodyPlayer->ApplyForce(b2Vec2(1.5, 0), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		cout << "Key " << sf::Keyboard::W << ": W is Pressed." << endl
			<< " Speed Up " << endl;
		bodyPlayer->ApplyForce(b2Vec2(0, -1), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		cout << "Key " << sf::Keyboard::R << ": R is Pressed." << endl
			<< " Reset Location " << endl;
		bodyDefPlayer.position = b2Vec2(
			25 / PIXEL_PER_METER, 25 / PIXEL_PER_METER
		);
		//bodyPlayer->ApplyForce(b2Vec2(0, -2), bodyPlayer->GetWorldCenter(), true);
	}

	// Box2D uses radians for rotation, SFML uses degree
	myPlayer.setRotation(bodyPlayer->GetAngle() * 180 / b2_pi);
	myPlayer.setPosition(bodyPlayer->GetPosition().x*PIXEL_PER_METER, bodyPlayer->GetPosition().y*PIXEL_PER_METER);

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
