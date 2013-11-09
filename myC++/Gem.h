#ifndef GEM_H
#define GEM_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "Object.h"


enum gemType{NORMAL_GEM,MYSTIC_GEM};

using namespace std;
class Gem : public Object
{
public:
	Gem();
	Gem(sf::Vector2f position, sf::RenderWindow* app,gemType GEMTYPE);
	~Gem();
	
	void giveHealth();
	void setSpriteImage(string path);
	void update();
	//collisions
	sf::Rect <float> gemBoundingBox;
	void updateBox();
	sf::Rect <float> getBoundingBox();
	gemType returnGemType();
private:
protected:
	//sf::RenderWindow* GameWindow;
	sf::Image iGem;
	sf::Sprite sGem;
	//sf::Vector2f position;
	sf::Vector2f prevPosition;
	gemType type;
};

#endif 