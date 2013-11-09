#include "Gem.h"

Gem::Gem()
{}

Gem::Gem(sf::Vector2f position, sf::RenderWindow* app,gemType GEMTYPE) : Object(app)
{
	
	this->position = position;		 
	this->type = GEMTYPE;

	if(returnGemType() == NORMAL_GEM)
		{
			setSpriteImage("images/Gem.png");
		}
	else if(returnGemType() == MYSTIC_GEM)
		{
			setSpriteImage("images/mysticGem.png");
		}
	
	sprite.SetPosition(position);
	
	gemBoundingBox.Top = sprite.GetPosition().y;
    gemBoundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    gemBoundingBox.Left = sprite.GetPosition().x;
    gemBoundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x; 


}
	
Gem::~Gem()
{
	printf("deleted GEM\n");
} //deconstructor for gem

void Gem::updateBox()
{
	gemBoundingBox.Top = sprite.GetPosition().y;
    gemBoundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    gemBoundingBox.Left = sprite.GetPosition().x;
    gemBoundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x; 
}

void Gem::setSpriteImage(string path)
{
	Object::setSpriteImage(path);

}

void Gem::update()
{
	updateBox();
}

sf::Rect<float> Gem::getBoundingBox()
{
	return gemBoundingBox;
}

gemType Gem::returnGemType()
{
	return type;
}