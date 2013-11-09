#include "Beetle.h"
#include "SFML\Graphics.hpp"

Beetle::Beetle()
{}

Beetle::Beetle(sf::Vector2f position, sf::RenderWindow* app) : Object(app)//custom constructor for the Player. 
{
	this->position = position;
	setSpriteImage("images/beetle.png");
	sprite.SetPosition(position);
	GameWindow=app;
	
	beetleBoundingBox.Top = sprite.GetPosition().y;
    beetleBoundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    beetleBoundingBox.Left = sprite.GetPosition().x;
    beetleBoundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x; 

	isRight=true;
}

Beetle::~Beetle()
{

}

void Beetle::moveLeft()
{
	if(isLeft == true)
	{
	sprite.FlipX(true);
	position.x -= 1.5;
	prevPosition=position;
	}
	return;
}

void Beetle::moveRight()
{
	if(isRight == true)
	{
	sprite.FlipX(false);
	position.x += 1.5;
	prevPosition=position;
	}
	return;
}

sf::Rect<float> Beetle::getBoundingBox()
{
	return beetleBoundingBox;
}

void Beetle::update()
{
	updateBoxes();
	moveLeft();
	moveRight();
	sprite.SetPosition(position);
}

void Beetle::checkPlatforms(vector<Block*> blocks)
{	
	bool left = false, right = false;

	for(vector<Block*>::iterator it = blocks.begin(); it!=blocks.end();it++)
	{
		if(rightCheck.Intersects((*it)->getBoundingBox()))
		{
			//printf("right is true");
			right = true;
		}

		if(leftCheck.Intersects((*it)->getBoundingBox()))
		{
			//printf("left is true");
			left = true;
		}

		if( left && right )
		{
			return;
		}
	}

	if( !right )
	{
		isLeft = true;
		isRight = false;
	}
	else
	{
		isLeft = false;
		isRight = true;
	}
}

void Beetle::updateBoxes()
{
	beetleBoundingBox.Top = sprite.GetPosition().y;
    beetleBoundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    beetleBoundingBox.Left = sprite.GetPosition().x+1;
    beetleBoundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x;  

	leftCheck.Top = sprite.GetPosition().y + sprite.GetSize().y;
	leftCheck.Left = sprite.GetPosition().x -5;
	leftCheck.Right = sprite.GetPosition().x;
	leftCheck.Bottom = sprite.GetPosition().y + sprite.GetSize().y + 5;

	rightCheck.Top = sprite.GetPosition().y + sprite.GetSize().y;
	rightCheck.Left = sprite.GetPosition().x +sprite.GetSize().x;
	rightCheck.Right = sprite.GetPosition().x + sprite.GetSize().x + 5;
	rightCheck.Bottom = sprite.GetPosition().y + sprite.GetSize().y +5;
}

bool Beetle::collidesWithGem(Gem* gem)
{
	if((beetleBoundingBox.Intersects(gem->getBoundingBox())) && (isLeft== true))
	{
		printf("MOVE RIGHT BEETLE\n");
	    position.x +=5;
		sprite.SetPosition(position);
		isLeft= false;
		isRight =true;
		sprite.FlipX(false);
	}
	else if((beetleBoundingBox.Intersects(gem->getBoundingBox())) && (isLeft!=true))
	{	
		printf("MOVE LEFT BEETLE\n");
		position.x -=5;
		sprite.SetPosition(position);
		isLeft=true;
		isRight=false;
		sprite.FlipX(true);
		//system("pause");
	}
	return true;
}


float Beetle::getPositionY()
{
	return position.y;
}

float Beetle::getPositionX()
{
	return position.x;
}
void Beetle::chargeLeft()
{
	position.x -= 5;
}
void Beetle::chargeRight()
{
	position.x += 5;
}