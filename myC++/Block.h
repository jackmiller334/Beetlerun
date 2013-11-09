#ifndef BLOCK_H
#define BLOCK_H
#include "Object.h"

enum blockType {NORMAL_BLOCK, DOWN_BLOCK, UP_BLOCK};

class Block : public Object
{
public:
	Block();
	Block(sf::Vector2f position, sf::RenderWindow* app,blockType BLOCKTYPE);
	~Block();
	void setSpriteImage(string path);
	float getPositionX();
	float getPositionY();
	sf::Rect<float> blockBoundingBox;
	sf::Rect<float> getBoundingBox();
	blockType returnblockType();

protected:
	sf::RenderWindow* GameWindow;
	sf::Image blockImage;
	sf::Sprite blockSprite;
	sf::Vector2f position;
	blockType type;
};

#endif
