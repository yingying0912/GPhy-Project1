#include <iostream>
#include <sstream>
#include <vector>

int main() {
		// Define Gravity in Vector 2 (X, Y)
		b2Vec2 gravity(0.0f, -10.0f);
		// Create World Obj with Gravity
		b2World world(gravity);

		// Define Body of the Ground Object
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);

		// Pass to Obj into World Obj
		b2Body* groundBody = world.CreateBody(&groundBodyDef);

		// Create Ground Polygon Obj
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);

		groundBody->CreateFixture(&groundBox, 0.0f);

		// Define Dynamic Body
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 4.0f);
		b2Body* body = world.CreateBody(&bodyDef);

		// Attaching Dynamic Body into Polygon
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);

		// Create Fixture Definition
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		// Simulate the World
		float timeStep = 1.0f / 60.0f;

		int32 velocityIterations = 6;
		int32 positionIterations = 2;

		for (int32 i = 0; i < 60; ++i)
		{
			world.Step(timeStep, velocityIterations, positionIterations);
			b2Vec2 position = body->GetPosition();
			float angle = body->GetAngle();
			printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		}
		
		return 0;
}