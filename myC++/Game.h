#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Beetle.h"
#include "Platform.h"
#include <time.h>
#include "Gem.h"
#include"Block.h"
#include <sstream>



enum gameState{SPLASH,LEVEL_ONE,LEVEL_TWO,GAME_OVER};
class Game
{
public:
	Game(); // default constructer
	Game(sf::RenderWindow* window); // custom constructor which is passing in a 'sf::RenderWindow' pointer
	~Game();//deconstructor
	
	void draw(sf::RenderWindow* window); //This initialises and draws sprites
	void getinput();//Handles input from the player
	void update(sf::RenderWindow* window);//This handles updating the game
	void play(sf::RenderWindow* window);//should be called in the game loop.
	void LoadLevel(sf::RenderWindow* window, string filePath);
	
	bool levelLoaded;
	bool levelCleared;
	void clearLevel();
	bool gameOver;
	bool outOfLives;
	bool paused;
	bool level2Cleared;
	int getPlayerLives();
	void endGame(sf::RenderWindow* window);

	int scoreLevel1;
	int scoreLevel2;
	int finalScore;

	void headsUpDisplay();

	void setGameState(gameState GameState);
	int playerLives;
	int counter;
	void splashScreen(sf::RenderWindow* window);

	Player *Player1;
	vector<Block*> blockVec;
	vector<Gem*>gemVec;
	Gem *gem1;
	Beetle *beetle;
	Exit *exit;
	gameState returnGameState();
	gameState state;
	sf::Image imageHud;
	sf::Sprite spriteHud;
private:
protected:
	sf::RenderWindow* GameWindow;
	sf::Clock Clock;

	sf::Image endImage;
	sf::Sprite endSprite;
	sf::Image backGround;
	sf::Sprite backGroundSprite;
	/*unsigned int height;
	unsigned int width;*/
};
#endif

