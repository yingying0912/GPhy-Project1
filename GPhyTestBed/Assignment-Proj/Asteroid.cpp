#include "Asteroid.h"

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
// Why? Refer to Computer Graphics
static const float PIXEL_PER_METER = 32.0f;

Asteroid::Asteroid(b2World& world, float radius, sf::Vector2f position)
{
	// Set Loc and Position
	circle_ = sf::CircleShape(radius);
	circle_.setOrigin(sf::Vector2f(radius, radius));
	bodyDef_.position = b2Vec2(
		position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER
	);
	bodyDef_.type = b2_dynamicBody;

	circle_.setFillColor(sf::Color(255, 255, 255, 255));
	circle_.setOutlineThickness(1);
	circle_.setOutlineColor(sf::Color::Black);

	bodyShape_.m_radius = radius / PIXEL_PER_METER;

	bodyFixtureDef_.shape = &bodyShape_;
	bodyFixtureDef_.density = .3f;
	bodyFixtureDef_.friction = .5f;

	body_ = world.CreateBody(&bodyDef_);
	body_->CreateFixture(&bodyFixtureDef_);
}

void Asteroid::setFillColor(sf::Color col)
{
	circle_.setFillColor(col);
}

void Asteroid::setOutlineThickness(float thickness)
{
	circle_.setOutlineThickness(thickness);
}

void Asteroid::setOutlineColor(sf::Color col)
{
	circle_.setOutlineColor(col);
}

void Asteroid::setTexture(sf::Texture* textures)
{
	circle_.setTexture(textures, true);
}

void Asteroid::update()
{
	// Box2D uses radians for rotation, SFML uses degree
	circle_.setRotation(body_->GetAngle() * 180 / b2_pi);
	circle_.setPosition(body_->GetPosition().x*PIXEL_PER_METER, body_->GetPosition().y*PIXEL_PER_METER);
}

sf::Shape& Asteroid::getShape()
{
	// TODO: insert return statement here
	return circle_;
}