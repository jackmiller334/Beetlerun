#include "Object.h"

Object::Object()
{
}

Object::Object(sf::RenderWindow *app)
{
	gameWindow = app;
}

void Object::objectInitialise(sf::Vector2f position)
{
	sprite.SetPosition(position); // this sets the sprite to a position vector.
}

void Object::draw()
{
	gameWindow->Draw(sprite);
}

void Object::setSpriteImage(string path)
{
	image.LoadFromFile( path.c_str() );
	image.CreateMaskFromColor(sf::Color(255,255,255,255) );
	sprite = sf::Sprite(image);
//	std::cout << path.c_str() << std::endl;
}

void Object::update()
{
}


Object::~Object(){}