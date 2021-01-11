#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "MyRectangle.h"

using namespace std;

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

int main()
{
	/*
		Timer for fixed update
	    50 (frames/times) per second
	*/ 
	float fixedTimeStep = 0.02f; 
	sf::Clock fixedUpdateClock;
	float timeElapsedSinceLastFrame = 0;

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
		Define/Create Border Areas
		-> Define with Window Size
	*/
	sf::Vector2f horizontalBorderSize(windowSizeX, windowBorderSize);
	sf::Vector2f verticalBorderSize(windowBorderSize, windowSizeY-windowBorderSize*2);
	sf::Vector2f topBorderPos(windowSizeX/2, windowBorderSize/2);
	sf::Vector2f bottomBorderPos(windowSizeX/2, windowSizeY-windowBorderSize/2);
	sf::Vector2f leftBorderPos(windowBorderSize/2, windowSizeY/2);
	sf::Vector2f rightBorderPos(windowSizeX-windowBorderSize/2, windowSizeY/2);

	
	//MyRectangle topBorder(world, horizontalBorderSize, topBorderPos, 0.0, false);
 //           	topBorder.setOutlineThickness(-1);
	//            topBorder.setOutlineColor(sf::Color::Black);
	//            topBorder.setFillColor(sf::Color(100, 100, 100));

	//MyRectangle bottomBorder(world, horizontalBorderSize, bottomBorderPos, 0.0, false);
 //             bottomBorder.setOutlineThickness(-1);
 //             bottomBorder.setOutlineColor(sf::Color::Black);
 //             bottomBorder.setFillColor(sf::Color(100, 100, 100));

	//MyRectangle leftBorder(world, verticalBorderSize, leftBorderPos, 0.0, false);
 //             leftBorder.setOutlineThickness(-1);
 //             leftBorder.setOutlineColor(sf::Color::Black);
 //             leftBorder.setFillColor(sf::Color(100, 100, 100));

	//MyRectangle rightBorder(world, verticalBorderSize, rightBorderPos, 0.0, false);
 //             rightBorder.setOutlineThickness(-1);
 //             rightBorder.setOutlineColor(sf::Color::Black);
 //             rightBorder.setFillColor(sf::Color(100, 100, 100));

	/*
		Create Vector/List of Boxes
		-> Use to Add Box that spawn
	*/
	vector<MyRectangle> boxList;
	sf::Vector2f dynamicBoxSize(32,32);

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

	// A buffer to check whether left mouse button has been clicked before or not
	bool leftMousePressed = false;

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

		// This is input handling without poll event
		// READ SFML DOCUMENTATION!
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if(!leftMousePressed)
			{
				sf::Vector2f pos = sf::Vector2f( sf::Mouse::getPosition(window) );
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

			// Update the objects that uses physics
			//topBorder.update();
			//bottomBorder.update();
			//leftBorder.update();
			//rightBorder.update();

			for(int i = 0; i < boxList.size(); i++){
				boxList[i].update();
			}

			// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
			// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
			timeElapsedSinceLastFrame -= fixedTimeStep;
		}

		// Rendering
		window.clear(sf::Color(100, 149, 237));	// CORNFLOWER BLUE!

		// Render all objects
		//window.draw(   topBorder.getShape());
		//window.draw(bottomBorder.getShape());
		//window.draw(  leftBorder.getShape());
		//window.draw( rightBorder.getShape());
		
		for(int i = 0; i < boxList.size(); i++)
		{
			window.draw(boxList[i].getShape());
		}

		ostringstream boxListStream;
		boxListStream << boxList.size();
		text.setString("Number of boxes: "+boxListStream.str());
		window.draw(text);
		window.display();
	}

	return 0;
}
