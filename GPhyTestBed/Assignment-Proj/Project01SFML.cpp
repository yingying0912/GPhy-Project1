/********************************************

	FILENAME -> Project01SFML.CPP

	Course : TGD2251 Game Physics
	Session: Trimester 2, 2020/21

	ID and Name #1 : 1171100974 Yee Cui Ying
	Contacts #1 : 010-225 9059 1171100974@student.mmu.edu.my

	ID and Name #2 : 1171100663 Muhammad Syafeeq bin Mohd Fauzi
	Contacts #2 : 011-23042570 1171100663@student.mmu.edu.my

********************************************/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

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
	float spawnTime = 1.0f, spawnrate = 1.f;
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

	sf::RectangleShape background;
	sf::Texture bg = loadImages("resources/Spaces.jpg");
	bg.setSmooth(true);
	background.setTexture(&bg);
	//background.setOrigin(windowSizeX/ 2, windowSizeY / 2);
	background.setSize(sf::Vector2f(800, 600));
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
	b2Vec2 gravity(0.001f, 0.1f);
	b2World world(gravity);

	/*
		Create Vector/List of Asteroids
		-> Use to Add Asteroids that spawn
	*/
	vector<Asteroid> astList;
	sf::Vector2f dynamicBoxSize(32,32);

	//flag for one time rectangle spawning when game launched
	bool gameStart = false;
	sf::Texture p_Texture = loadImages("resources/Player_32.png");
	Player player(world, dynamicBoxSize, sf::Vector2f(windowSizeX/2, windowSizeY-10), 0, sf::Color::White, 1, sf::Color::Black, &p_Texture);
	player.setOutlineThickness(0);

	sf::Texture a_Texture;
	/*
		Define Properties of Fonts
		-> Sizes, Font Design, Position, Color
	*/
	sf::Font font = loadFont();

	sf::Text H_Text;
	H_Text.setFont(font);  
	H_Text.setCharacterSize(32);
	H_Text.setPosition(3, -3);
	H_Text.setFillColor(sf::Color::White);

	sf::Text Asteroid_Text;
	Asteroid_Text.setFont(font);
	Asteroid_Text.setCharacterSize(16);
	Asteroid_Text.setPosition(3, 24);
	Asteroid_Text.setFillColor(sf::Color::White);

	sf::Text Game_Over;
	Game_Over.setFont(font);
	Game_Over.setCharacterSize(64);
	Game_Over.setOrigin(144, 32);
	Game_Over.setPosition(windowSizeX / 2, windowSizeY / 2);	
	Game_Over.setFillColor(sf::Color::White);

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
				position.y = rand() % (windowSizeY/2);
				float myRadius = rand() % 15 + 2;

				a_Texture = loadImages("resources/Meteroid_32.png");
				Asteroid Ast(world, myRadius, position, sf::Color(255, 255, 255), 0, sf::Color(255, 255, 255, 0), &a_Texture);
				astList.push_back(Ast);
			}
			gameStart = true;
		}

		/* spawn 2 astroid every 1 second */
		currentTime += fixedUpdateClock.getElapsedTime().asSeconds();
		if (currentTime >= spawnTime){
			
			for (int i = 0; i < spawnrate; i++) {
				sf::Vector2f position;
				position.x = rand() % windowSizeX;
				position.y = -32;
				float myRadius = rand() % 32 + 5;

				a_Texture = loadImages("resources/Meteroid_32.png");
				Asteroid Ast(world, myRadius, position, sf::Color(255, 255, 255), 0, sf::Color(255,255,255,0) , &a_Texture);

				astList.push_back(Ast);
			}

			currentTime = 0;
			if (spawnrate <= 3.f) {
				spawnrate += 0.1f;
			}
			
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
			player.update(windowSizeX, windowSizeY);
			player.update();

			for (int i = 0; i < astList.size(); i++) {
				astList[i].update();
			}

			for (int i = 0; i < astList.size(); i++) {
				sf::Vector2f astData = astList[i].getShape().getPosition();
				if (astData.y > windowSizeY) {
					astList[i].getBody()->GetWorld()->DestroyBody(astList[i].getBody());
					astList.erase(astList.begin() + i);
				}
				if (astData.x > windowSizeX) {
					astList[i].getBody()->ApplyForce(b2Vec2(-1, 1), astList[i].getBody()->GetWorldCenter(), true);
				}
				if (astData.x < 0) {
					astList[i].getBody()->ApplyForce(b2Vec2(1, 1), astList[i].getBody()->GetWorldCenter(), true);
				}
			}

			int collide = collision(player, astList);
			if (collide)
			{
				player.damaged();
				player.reset(windowSizeX / 2, windowSizeY);
				astList.erase(astList.begin() + collide);
			}

			// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
			// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
			timeElapsedSinceLastFrame -= fixedTimeStep;
		}

		// Rendering
		window.clear(sf::Color(100, 149, 237));	// CORNFLOWER BLUE!
		window.draw(background);
		
		// Render all objects
		for (int i = 0; i < astList.size(); i++)
		{
			window.draw(astList[i].getShape());
		}

		window.draw(player.getShape());

		ostringstream Heart;
		Heart << player.getCurrentHealth();

		ostringstream astListStream;
		astListStream << astList.size();


		H_Text.setString("Current Health: [" + Heart.str() + "]");
		window.draw(H_Text);

		Asteroid_Text.setString("Number of Asteroids: " + astListStream.str());
		window.draw(Asteroid_Text);

		Game_Over.setString("GAME OVER");

		if (player.getCurrentHealth() <= 0)
		{
			window.draw(Game_Over);

			currentTime = 0;
			timeElapsedSinceLastFrame = 0;
		}

		window.display();
	}

	return 0;
}

void update(Player player, vector<Asteroid> astList){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		player.update(b2Vec2(0,-2));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		player.update(b2Vec2(-1.5,0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.update(b2Vec2(1.5,0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < astList.size(); i++) {
			astList[i].moveForward();
		}
	}
}

int collision(Player player, vector<Asteroid> astList){

	for (int i = 0; i < astList.size(); i++) {
		if (player.getShape().getGlobalBounds().intersects(astList[i].getShape().getGlobalBounds())) {
			player.setFillColor(sf::Color::Red);
			return i;
		}
		else { player.setFillColor(sf::Color::White); }
	}
	return 0;
}
