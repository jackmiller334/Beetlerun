#ifndef __OBJECT__
#define __OBJECT__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
class Object
{
public:
	Object();
    Object(sf::RenderWindow* App );
	virtual ~Object();
	virtual void objectInitialise(sf::Vector2f position);
	virtual void draw();
	virtual void setSpriteImage(string path);
	virtual void update();
protected:
	sf::RenderWindow* gameWindow;
	sf::Sprite sprite;
	sf::Image image;
	sf::Vector2f position;
	sf::Vector2f velocity;
};
#endif