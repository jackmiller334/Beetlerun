#include "Exit.h"

Exit::Exit() {}
Exit::Exit(sf::Vector2f position, sf::RenderWindow*app) :Object(app)
{
	this->position = position;
	setSpriteImage("images/Exit.png");
	sprite.SetPosition(position);

	exitBoundingBox.Top = sprite.GetPosition().y;
    exitBoundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    exitBoundingBox.Left = sprite.GetPosition().x;
    exitBoundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x; 
}

Exit::~Exit(){}

sf::Rect<float> Exit::getBoundingBox()
{
	return exitBoundingBox;
}