/********************************************

	FILENAME -> Project01SFML.CPP

	Course : TGD2251 Game Physics
	Session: Trimester 2, 2020/21

	ID and Name #1 : 1171100974 Yee Cui Ying
	Contacts #1 : 010-225 9059 EMailOfStud1

	ID and Name #2 : 1171100663 Muhammad Syafeeq bin Mohd Fauzi
	Contacts #2 : 011-23042570 fauzisyafeeq@gmail.com

********************************************/



#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "MyRectangle.h"
#include "Player.h"
#include "Asteroid.h"

using namespace std;

void update(Player player, vector<Asteroid> astList);
int collision(Player player, vector<Asteroid> astList);
void reset(Player player);

sf::Font loadFont(const string& fontFilename = "resources/04b03.ttf")
{
	sf::Font myFont;
	if (!myFont.loadFromFile(fontFilename))
	{
		cout << "Could not load Font -> " << fontFilename << endl;
		exit(1);
	}

	return myFont;
}

sf::Texture loadImages(string fontFilename)
{
	sf::Texture myImages;
	if (!myImages.loadFromFile(fontFilename))
	{
		cout << "Could not load Font -> " << fontFilename << endl;
		exit(1);
	}

	return myImages;
}

int main()
{
	// random algorithm
	srand (time(NULL));
	/*
		Timer for fixed update
	    50 (frames/times) per second
	*/ 
	float fixedTimeStep = 0.02f; 
	sf::Clock fixedUpdateClock;
	float timeElapsedSinceLastFrame = 0;

	// spawn cd
	float spawnTime = 1.0f;
	float currentTime = 0.0f;

	/*
		Create Windows Application
		-> Set Size Width, Height
		-> Renders with its Size and Title Name
	*/
	int windowSizeX = 800, 
		windowSizeY = 600,
		windowBorderSize = 16;

	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Project 01");

	/*
		Set the Windows vSync to true and Activate
		(and as a result, we have a cap of 60FPS)
	*/ 
	window.setVerticalSyncEnabled(true);
	window.setActive();

	/*
		Basic Box2D Creation
		-> Create Gravity and World
		- -> assign Gravity to World
	*/ 
	b2Vec2 gravity(0.1f, 0.1f);
	b2World world(gravity);

	/*
		Create Vector/List of Boxes
		-> Use to Add Box that spawn
	*/
	vector<MyRectangle> boxList;
	vector<Asteroid> astList;
	sf::Vector2f dynamicBoxSize(32,32);

	//flag for one time rectangle spawning when game launched
	bool gameStart = false;
	sf::Texture p_Texture = loadImages("resources/Player_32.png");
	Player player(world, dynamicBoxSize, sf::Vector2f(windowSizeX/2, windowSizeY), 0, sf::Color::White, 1, sf::Color::Black, &p_Texture);
	player.setOutlineThickness(0);
	/*
		Define Properties of Fonts
		-> Sizes, Font Design, Position, Color
	*/
	sf::Font font = loadFont();
	sf::Text text;
	text.setFont(font);  
	text.setCharacterSize(16);
	text.setPosition(3, -3);
	text.setFillColor(sf::Color::White);

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(16);
	text2.setPosition(3, 7);
	text2.setFillColor(sf::Color::White);

	// A buffer to check whether left mouse button has been clicked before or not
	//bool leftMousePressed = false;

	while(window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event));
		{
			// This is input handling via poll event
			// Do not use this for game input
			// Why? Delay issues
			// READ SFML DOCUMENTATION!
			//if(event.type == sf::Event::Closed) window.close();
		}

		// close window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
		}

		/* initial rectangle spawning */
		if (!gameStart){

			for (int i = 0; i < 20; i++) {
				sf::Vector2f position;
				position.x = rand() % windowSizeX;
				position.y = rand() % windowSizeY;
				float myRadius = rand() % 15 + 2;

				string astFile;
				if (myRadius >= 8.f) { 
					astFile = "resources/Meteroid_8.png"; 
					cout << "my radius is more than 8" << endl; 
				}
				else if (myRadius >= 4.f) { 
					astFile = "resources/Meteroid_4.png";  
					cout << "my radius is more than 4" << endl;
				}
				else if (myRadius >= 2.f) { 
					astFile = "resources/Meteroid_2.png";   
					cout << "my radius is more than 2" << endl;
				}

				sf::Texture ast_T = loadImages(astFile);
				Asteroid Ast(world, myRadius, position, sf::Color(100, 100, 200), 1, sf::Color::Black, &ast_T);
				astList.push_back(Ast);
			}
			gameStart = true;
		}
		
	/*
		// This is input handling without poll event
		// READ SFML DOCUMENTATION!
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if(!leftMousePressed)
			{
				sf::Vector2f pos = sf::Vector2f( sf::Mouse::getPosition(window) );
				float x = pos.x;
				float y = pos.y;
				cout << pos.x << " " << pos.y << endl;
				MyRectangle r(world, dynamicBoxSize, pos);
				r.setOutlineThickness(1);
				r.setOutlineColor(sf::Color::Black);
				r.setFillColor(sf::Color(100, 100, 200));
				boxList.push_back(r);
				leftMousePressed = true;
			}
		}
		else
		{
			leftMousePressed = false;
		}
	*/

		/* spawn 5 rectangles every 1 second */
		currentTime += fixedUpdateClock.getElapsedTime().asSeconds();
		if (currentTime >= spawnTime){
			
			for (int i = 0; i < 1; i++) {
				sf::Vector2f position;
				position.x = rand() % windowSizeX;
				position.y = 0;
				float myRadius = rand() % 32 + 5;

				string astFile;
				if (myRadius >= 32.f) {
					astFile = "resources/Meteroid_32.png";
					cout << "my radius is more than 32" << endl;
				}
				else if (myRadius >= 24.f) {
					astFile = "resources/Meteroid_24.png";
					cout << "my radius is more than 24" << endl;
				}
				else if (myRadius >= 8.f) {
					astFile = "resources/Meteroid_8.png";
					cout << "my radius is more than 8" << endl;
				}
				else if (myRadius >= 4.f) { 
					astFile = "resources/Meteroid_4.png";
					cout << "my radius is more than 4" << endl;
				}
				else if (myRadius >= 2.f) { 
					astFile = "resources/Meteroid_2.png";
					cout << "my radius is more than 2" << endl;
				}

				sf::Texture ast_T = loadImages(astFile);
				Asteroid Ast(world, myRadius, position, sf::Color(100, 100, 200), 1, sf::Color::Black, &ast_T);

				astList.push_back(Ast);
			}

			currentTime = 0;
		}


		// We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
		timeElapsedSinceLastFrame += fixedUpdateClock.restart().asSeconds();

		// If sufficient time has elapsed, we update the physics
		if(timeElapsedSinceLastFrame >= fixedTimeStep)
		{

			// Step is used to update physics position/rotation
			world.Step(
				fixedTimeStep,		//update	frequency
                8,					//velocity	Iterations
                3					//position	Iterations  
            );

			// ------ Update the objects that uses physics
			update(player, astList);
			player.update();

			for (int i = 0; i < astList.size(); i++) {
				astList[i].update();
			}

			int collide = collision(player, astList);
			if (collide){
				cout << "Collision occurred" << endl;
				player.damaged();
				player.reset(windowSizeX/2, windowSizeY);
				astList.erase(astList.begin() + collide);
			}

			// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
			// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
			timeElapsedSinceLastFrame -= fixedTimeStep;
		}

		// Rendering
		window.clear(sf::Color(100, 149, 237));	// CORNFLOWER BLUE!

		// Render all objects

		for (int i = 0; i < astList.size(); i++)
		{
			window.draw(astList[i].getShape());
		}

		window.draw(player.getShape());

		ostringstream boxListStream;
		boxListStream << boxList.size();

		ostringstream astListStream;
		astListStream << astList.size();

		text.setString("Number of boxes: "+boxListStream.str());
		window.draw(text);

		text2.setString("Number of Asteroids: " + astListStream.str());
		window.draw(text2);


		window.display();

		if (player.getCurrentHealth() <= 0){
			currentTime = 0;
			timeElapsedSinceLastFrame = 0;
		}
	}

	return 0;
}

void update(Player player, vector<Asteroid> astList){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		/*cout << "Key " << sf::Keyboard::Space << ": Space is Pressed." << endl
			<< " Booster Launched! " << endl;*/
		player.update(b2Vec2(0,-2));
		//bodyPlayer->ApplyForce(b2Vec2(0, -2), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		/*cout << "Key " << sf::Keyboard::A << ": A is Pressed." << endl
			<< " Going Left " << endl;*/
		player.update(b2Vec2(-1.5,0));
		//bodyPlayer->ApplyForce(b2Vec2(-1.5, 0), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		/*cout << "Key " << sf::Keyboard::D << ": D is Pressed." << endl
			<< " Going Right " << endl;*/
		player.update(b2Vec2(1.5,0));
		//bodyPlayer->ApplyForce(b2Vec2(1.5, 0), bodyPlayer->GetWorldCenter(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		/*cout << "Key " << sf::Keyboard::W << ": W is Pressed." << endl
			<< " Speed Up " << endl;*/
		for (int i = 0; i < astList.size(); i++) {
			astList[i].moveForward();
		}
		//bodyPlayer->ApplyForce(b2Vec2(0, -1), bodyPlayer->GetWorldCenter(), true);
		//Asteroid.moveForward();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		/*cout << "Key " << sf::Keyboard::R << ": R is Pressed." << endl
			<< " Reset Location " << endl;*/
		//bodyDefPlayer.position = b2Vec2(
		//	25 / PIXEL_PER_METER, 25 / PIXEL_PER_METER
		//);
		//bodyPlayer->ApplyForce(b2Vec2(0, -2), bodyPlayer->GetWorldCenter(), true);
	}
}

int collision(Player player, vector<Asteroid> astList){
	// Check Intersections!
	for (int i = 0; i < astList.size(); i++) {
		if (player.getShape().getGlobalBounds().intersects(astList[i].getShape().getGlobalBounds())) {
			return i;
			//astList[i].setFillColor(sf::Color::White);
		}
	}
	return 0;
}
