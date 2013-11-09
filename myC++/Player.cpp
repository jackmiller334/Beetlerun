#include "Player.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

Player::Player()
{}

Player::Player(sf::Vector2f position,sf::RenderWindow* app) : Object(app)//custom constructor for the Player. 
{
	this->position= position;
	velocity.x = 0;
	velocity.y = 0;
	setSpriteImage("images/Player.png");
	collideFloor = false;
	sprite.SetPosition(position);
	prevPosition = position;
	Object::objectInitialise(position);
	setCollisions();
	updateBoxes();
	exitHit=false;
	playerHealth=10;
	superJump=false;
}


void Player::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Player::setCollisions()
{
	topBoxCollide = false;
	bottomBoxCollide = false;
	leftBoxCollide = false;
	rightBoxCollide = false;

	return;
}

Player::~Player()
{
}

void Player::setSpriteImage(string path)
{
	Object::setSpriteImage(path);
	return;
}


void Player::getInput()
{

	if(!gameWindow->GetInput().IsKeyDown( sf::Key::Left))
		{
			friction();
		}
	if(gameWindow->GetInput().IsKeyDown( sf::Key::Left))
	{
		moveLeft();
	}
	if(gameWindow->GetInput().IsKeyDown( sf::Key::Right))
	{
		moveRight();
	}
	if(!gameWindow->GetInput().IsKeyDown( sf::Key::Right))
	{
		friction();
	}
	if(gameWindow->GetInput().IsKeyDown(sf::Key::Space))
	{
		if(playerHealth>5)
		{
		jump();
		collideFloor=false;
		}
	}
	if(gameWindow->GetInput().IsKeyDown( sf::Key::Down))
	{
	
	}
}

void Player::Stop()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Player::gravity()
{
		prevPosition=position;
		
		velocity.y += GRAVITY;
		position.y += velocity.y;
}

void Player::updatePlayer()
{
	float healthClock = clock.GetElapsedTime();
	if(healthClock > 1)
	{
	//	printf("HEALTH DOWN\n");
		playerHealth -= 2;
		cout << playerHealth <<endl;
		clock.Reset();
	}

	gravity();
	getInput();
	sprite.SetPosition(position);
	updateBoxes();
}
bool Player::collidesWithGem(Gem* gem)
{

	if(boundingBox.Intersects(gem->getBoundingBox()))
	{
		if(gem->returnGemType() == NORMAL_GEM)
		{
		playerHealth +=10;
		//printf("GEM COLLIDE");
		return true;
		}
		if(gem->returnGemType() == MYSTIC_GEM)
		{
		playerHealth +=10;
		//printf("MYSTIC GEM COLLIDE");
		//cout << "SUPER JUMP ENABLED" << endl;
		superJump = true;
		return true;
		}
	}
	return false;
}



//RETURNS TRUE IF THE PLAYER HAS COLLIDED WITH A BEETLE
bool Player::collidesWithBeetle(Beetle* beetle)
{
	if(boundingBox.Intersects(beetle->getBoundingBox()))
	return true;
}
//RETURNS TRUE IF THE PLAYER HAS COLLIDED WITH THE EXIT
bool Player::collidesWithExit(Exit* exit)
{
	if(boundingBox.Intersects(exit->getBoundingBox()))
	{
		//printf("COLLIDE WITH EXIT");
		return true;
	}
	return false;
}

//RETURNS TRUE IF THE PLAYER HAS COLLIDED WITH A BLOCK
bool Player::collidesWithBlock(Block* block)
{
	if( playerBoundingBoxTop.Intersects( block->getBoundingBox()))
	{
		if(block->returnblockType() == NORMAL_BLOCK)
		{
			position.y = prevPosition.y;
			sprite.SetPosition(position);
			setCollisions();
		}
		if(block->returnblockType() == UP_BLOCK)
		{
			position.y -= 80;
			//position.y = prevPosition.y;
			sprite.SetPosition(position);
			//system("pause");
			setCollisions();
		}
	}

	if ( playerBoundingBoxBottom.Intersects(block->getBoundingBox()))
	{
		collideFloor = true;
	
       if(block->returnblockType() == NORMAL_BLOCK || block->returnblockType() == UP_BLOCK )
		{
		velocity.y = 0;
		position.y = prevPosition.y;
		sprite.SetPosition(position);

		}
	else if(block->returnblockType() == DOWN_BLOCK)// CHECKING BLOCK TYPE 
		{
	
			position.y += 80;
			
			sprite.SetPosition(position);
			
			setCollisions();
		}
	}

	if ( playerBoundingBoxLeft.Intersects(block->getBoundingBox()))
	{
		leftBoxCollide = true;
	}

	if( playerBoundingBoxRight.Intersects(block->getBoundingBox()))
	{
		rightBoxCollide = true;
	}
	

	if ( rightBoxCollide == true)
	{

		position.x = prevPosition.x;
		velocity.x = 0;
	
	}

	if ( leftBoxCollide == true)
	{
		position.x = prevPosition.x;
		velocity.x = 0;
		
	}

	if(topBoxCollide || bottomBoxCollide || leftBoxCollide || rightBoxCollide)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

//UPDATES THE BOXES SO THAT THEY STAY WITH THE PLAYER WHEN HE MOVES.
void Player::updateBoxes()
{
	playerBoundingBoxTop.Top = sprite.GetPosition().y;
    playerBoundingBoxTop.Bottom = sprite.GetPosition().y + 10; 
    playerBoundingBoxTop.Left = sprite.GetPosition().x + 10; 
    playerBoundingBoxTop.Right = sprite.GetPosition().x + sprite.GetSize().x - 10; 

	playerBoundingBoxBottom.Top = sprite.GetPosition().y + sprite.GetSize().y - 10;
    playerBoundingBoxBottom.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    playerBoundingBoxBottom.Left = sprite.GetPosition().x + 10; 
    playerBoundingBoxBottom.Right = sprite.GetPosition().x + sprite.GetSize().x - 10;

    playerBoundingBoxLeft.Top = sprite.GetPosition().y + 10;
    playerBoundingBoxLeft.Bottom = sprite.GetPosition().y + sprite.GetSize().y - 10;
    playerBoundingBoxLeft.Left = sprite.GetPosition().x - 2;
    playerBoundingBoxLeft.Right = sprite.GetPosition().x;

    playerBoundingBoxRight.Top = sprite.GetPosition().y + 10;
    playerBoundingBoxRight.Bottom = sprite.GetPosition().y + sprite.GetSize().y - 10;
    playerBoundingBoxRight.Right = sprite.GetPosition().x + sprite.GetSize().x +2;
    playerBoundingBoxRight.Left = sprite.GetPosition().x + sprite.GetSize().x;

    boundingBox.Top = sprite.GetPosition().y;
    boundingBox.Bottom = sprite.GetPosition().y + sprite.GetSize().y;
    boundingBox.Left = sprite.GetPosition().x;
    boundingBox.Right = sprite.GetPosition().x + sprite.GetSize().x; 
}

void Player::setPositionY(float posY)
{
	position.y += posY;
}

void Player::acceleration()
{
	if( velocity.x < 0.0 )
	{
		velocity.x = 0.0;
	}
	
	velocity.x = velocity.x += ACCELERATION;

	if( velocity.x > MAX_VEL )
	{
		velocity.x = MAX_VEL;
	}
	return;
}

void Player::friction()
{
	velocity.x -= FRICTION;
	
	if(velocity.x < 0.0)
	{
		velocity.x = 0.0;
	}
	return;
}

void Player::moveLeft()
{
	sprite.FlipX(true);
	prevPosition.x = position.x;
	//- velocity to position.x
	velocity.x += ACCELERATION;
	position.x -=velocity.x;

	if(velocity.x > MAX_VEL)
	{
		velocity.x = MAX_VEL;
	}
	return;
}

void Player::moveRight()
{
	sprite.FlipX(false);
	prevPosition.x = position.x;
	velocity.x +=ACCELERATION;
	position.x += velocity.x;

	if(velocity.x > MAX_VEL)
	{
		velocity.x = MAX_VEL;
	}
}

void Player::jump()
{
	if(!superJump)
	position.y -= 10;
	else
	position.y -= 15;
}

float Player::getPositionX()
{
	return position.x;
}

float Player::getPositionY()
{
	return position.y;
}

void Player::attacked(Beetle* beetle)
{
	float beetlePositionX;
	float beetlePositionY;
	beetlePositionX = beetle->getPositionX();
	beetlePositionY = beetle->getPositionY();

	float upValue = beetle->getPositionY() - 10;
	float downValue = beetle->getPositionY() +10;
	
	
	if(((collideFloor==true) && (position.y < downValue) && (position.y > upValue)))
	{
		if((beetle->isRight==true) && (position.x > beetlePositionX))
		{
			//printf("CHARGE RIGHT");
			beetle->chargeRight();
		}
		if((beetle->isLeft==true) && (position.x < beetlePositionX))
		{
			//printf("CHARGE LEFT");
			beetle->chargeLeft();
		}
	}
}

int Player::getPlayerHealth()
{

	return playerHealth;
}