#ifndef __EXIT__
#define __EXIT__
#include "Object.h"

class Exit : public Object
{
public:
	Exit();
	Exit(sf::Vector2f position,sf::RenderWindow* app);
	~Exit();

	//collisions//
	sf::Rect<float> exitBoundingBox;
	sf::Rect<float> getBoundingBox();
private:
protected:
	sf::RenderWindow* GameWindow;
	sf::Image blockImage;
	sf::Sprite blockSprite;
	sf::Vector2f position;

};

#endif