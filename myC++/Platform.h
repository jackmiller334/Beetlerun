#ifndef Platform_H
#define Platform_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class Platform
{
public:
	Platform();
	Platform(sf::Vector2f position, sf::RenderWindow* app);
	~Platform();

private:
protected:
	sf::RenderWindow* GameWindow;
	sf::Vector2f position;
};

#endif 