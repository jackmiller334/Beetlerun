#ifndef Player_H
#define Player_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "Object.h"
#include "Block.h"
#include "Beetle.h"
#include "Exit.h"
using namespace std;

const float GRAVITY = 0.4;
const float ACCELERATION = 0.59;
const float MAX_VEL =10;
const float FRICTION = 0.3;
const float MAX_JUMP_VEL = 5;
const float FRAME_RATE = 30.0;


class Player : public Object
{
public:
	Player();
	Player(sf::Vector2f position,sf::RenderWindow* app);
	~Player();

	

	int playerHealth;
	int getPlayerHealth();

	//METHODS
	void attacked(Beetle* beetle);
	void load();
	void Stop();
	void setVelX(int velX);
	void setPositionY(float posY);
	void getInput();
	void moveLeft();
	void moveRight();
	void friction();
	void acceleration();
	void gravity();
	void updatePlayer();
	void jump();
	void setSpriteImage(string path);
	void setPosition(sf::Vector2f position);
	float getPositionX();
	float getPositionY();
	
	//BOOLS / FLAGS
	bool isLeft;		
	bool isRight;		
	bool moveDown();	
	bool moveUp();
	bool collideFloor;
	bool exitHit;
	bool superJump;


	// COLLISIONS
	sf::Rect<float> playerBoundingBoxTop,playerBoundingBoxBottom,playerBoundingBoxLeft,playerBoundingBoxRight;
	sf::Rect<float> boundingBox;
	bool collidesWithBlock(Block* block);
	bool collidesWithBeetle(Beetle* beetle);
	bool collidesWithGem(Gem* gem);
	bool collidesWithExit(Exit* exit);
	void updateBoxes();
	void setCollisions();
	bool topBoxCollide,bottomBoxCollide, leftBoxCollide, rightBoxCollide;
	//////////////
	
private:
protected:
	sf::RenderWindow* GameWindow;
	sf::Clock clock;
	sf::Image iPlayer;
	sf::Sprite sPlayer;
	sf::Vector2f position;
	sf::Vector2f prevPosition;
	
	
};

#endif 
