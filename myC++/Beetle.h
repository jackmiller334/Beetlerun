#ifndef Beetle_H
#define Beetle_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "Object.h"
#include "Block.h"
#include "Gem.h"

class Beetle : public Object
{
public:
	Beetle();
	Beetle(sf::Vector2f position, sf::RenderWindow* app);
	~Beetle();
	void moveLeft();
	void moveRight();
	bool moveDown();
	void update();
	void checkPlatforms(vector<Block*>block);
	void updateBoxes();
	float getPositionX();
	float getPositionY();
	void chargeRight();
	void chargeLeft();
	bool isLeft, isRight;
	bool start;

	//collisions
	sf::Rect<float> getBoundingBox();
	sf::Rect<float> beetleBoundingBox;
	sf::Rect<float> leftCheck;
	sf::Rect<float> rightCheck;
	bool collidesWithGem(Gem* gem);
	void resetCollisions();
private:
protected:
	sf::RenderWindow* GameWindow;
	sf::Image iBeetle;
	sf::Sprite sBeetle;
	sf::Vector2f position;
	sf::Vector2f prevPosition;
	vector<Block*>block;
	//Player* player1;
};

#endif