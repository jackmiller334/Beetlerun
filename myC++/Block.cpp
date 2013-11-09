#include "Block.h"

Block::Block()
{}
Block::Block(sf::Vector2f position, sf::RenderWindow* app,blockType BLOCKTYPE) : Object(app)
{
	this->position = position;
	this->type = BLOCKTYPE;

	if(returnblockType() == NORMAL_BLOCK)
		{
			setSpriteImage("images/Block.png");
		}
	else if(returnblockType() == UP_BLOCK)
		{
			setSpriteImage("images/BlockU.png");
		}
	else if(returnblockType() == DOWN_BLOCK)
		{
			setSpriteImage("images/BlockD.png");
		}
	


	sprite.SetPosition(position);
	blockBoundingBox.Top = sprite.GetPosition().y;
    blockBoundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    blockBoundingBox.Left = sprite.GetPosition().x;
    blockBoundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x; 

	
}

Block::~Block(){} //deconstructor


void Block::setSpriteImage(string path)
{
	Object::setSpriteImage(path);
	return;
}

float Block::getPositionX()
{
	return position.x;
}

float Block::getPositionY()
{
	return position.y;
}

sf::Rect<float> Block::getBoundingBox()
{
	return blockBoundingBox;
}

blockType Block::returnblockType()
{
	return type;
}