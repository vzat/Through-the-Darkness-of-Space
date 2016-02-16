#ifndef GAME_H
#define GAME_H

// Dependencies
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>
#include <AstroObject.h>
#include <Sun.h>
#include <Planet.h>
#include <SolarSystem.h>

// Game
class Game {
	private:
		sf::RenderWindow window;
		sf::VideoMode screen;
		sf::ContextSettings settings;
		sf::Font font;
		int keys[512] = { 0 };
		int stop;
		std::vector<std::unique_ptr<AstroObject>> astro;
		SolarSystem solarSystem;
		sf::Vector2<double> view;
		float ppm;
		int frames;
		sf::Clock clock;
		sf::Clock frameTime;
		sf::Text frameRate;
		float dt;
		float accumulator;
	public:
		Game();
		~Game();
		void events();
		int getStop();
		float dist(double x1, double y1, double x2, double y2);
		float semiMajorAxis(int i);
		float eccentricityVector(int i);
		float apoapsis(int i);
		void keyPressed();
		void update();
		void render();
};


#endif