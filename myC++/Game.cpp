#include "Game.h"
#include "SFML/Graphics.hpp" // The graphics package for drawing.
#include <iostream> // Used for testing purposes primarily.


Game::Game()
{}

//DECONSTRUCTOR FOR GAME CALLED WHEN GAME QUITS TO CLEAN UP OBJECTS.
Game::~Game()
{
	for( vector<Block*>::iterator i = blockVec.begin(); i != blockVec.end(); )
	{
		delete (*i);
		i = blockVec.erase( i );
	}

	for( vector<Gem*>::iterator i = gemVec.begin(); i != gemVec.end(); )
	{
		delete (*i);
		i = gemVec.erase( i );
	}

	delete exit;
	delete beetle;
	delete Player1;
}


//LEVEL LOADER////
void Game::LoadLevel(sf::RenderWindow* window, string filePath)
{

    std::fstream levelFile; // open an fstream called LevelFile to read a file
    string fileLine; // make a string called fileLIne

    int blockX = 0;
    int blockY = 0;

    levelFile.open(filePath); // open a file 

    while( blockY<=15)
    {
        getline(levelFile,fileLine);
        stringstream SS; // create a stringstream to manipulate strings
        SS.clear(); // Clear the stringstream
        SS.str(fileLine);

        while(blockX <=20)
        {
            char character; // make a char called 'CHARACTER'
            SS >> character;
		
            if(character =='B')
            {

                Block *block = new Block(sf::Vector2f(blockX * 40, blockY * 40),window,NORMAL_BLOCK);

                blockVec.push_back(block);

            }
			else if(character =='U')
			{
                Block *block = new Block(sf::Vector2f(blockX * 40, blockY * 40),window,UP_BLOCK);
        
                blockVec.push_back(block);
		
			}
			else if(character=='D')
			{
				Block *block = new Block(sf::Vector2f(blockX * 40,blockY * 40),window,DOWN_BLOCK);
				blockVec.push_back(block);
		
			}
			else if(character=='O')
			{
				beetle = new Beetle(sf::Vector2f(blockX * 40, blockY * 40),window);
			//	printf("printed Beetle");
			}
			else if(character=='E')
			{
				exit = new Exit(sf::Vector2f(blockX * 40, blockY * 40),window);
			}

            else if(character =='/')
            {
           //     cout << "BLANK" << endl;
            }
            else if(character =='P')
            {	
				Player1 = new Player(sf::Vector2f(blockX * 40, blockY * 40),window);
            }
			else if(character=='G')
			{
				Gem *gem = new Gem(sf::Vector2f(blockX * 40, blockY * 40),window,NORMAL_GEM);
				gemVec.push_back(gem);
			//	printf("PUSHED BACK GEM\n");
			}
			else if(character=='M')
			{
				Gem *gem = new Gem(sf::Vector2f(blockX * 40,blockY * 40),window,MYSTIC_GEM);
				gemVec.push_back(gem);
			}
             ++blockX;
            SS.clear(); 
        }
          blockX = 0;
        ++blockY;
    }
	levelLoaded=true;
}

Game::Game(sf::RenderWindow* window) : GameWindow(window)
{	

	backGround.LoadFromFile("images/backGround.png");
	backGroundSprite.SetImage(backGround);

	playerLives = 3;// sets the initial lives for the player
	state = LEVEL_ONE;
	levelLoaded=false;
	levelCleared=false;
	level2Cleared=false;
	gameOver=false;
	outOfLives=false;
	counter=0;
	paused=false;
	endImage.LoadFromFile("images/gameOver.png");
	endSprite.SetImage(endImage);
	

//	Player1 = new Player(sf::Vector2f(100,500),window);
}
void Game::draw(sf::RenderWindow* window)
{
	/*//if(playerLives==0)
	{ //
	*///}
	switch (state)
	{
		case(LEVEL_ONE):

			if(levelLoaded==false)
			{
				LoadLevel(window,"level.dat");
			}
			break;
		case(LEVEL_TWO):
			if(levelCleared==true)
			{
			clearLevel();
			levelLoaded=false;
			}
			if(levelLoaded==false)
			{
				LoadLevel(window,"levelTwo.dat");
				//levelLoaded=true;
				level2Cleared=true;
			}
		break;
		case(GAME_OVER):
			{
			endGame(window);
			printf("REACHED GAME OVER STAGE");
			}
	}

	GameWindow->Clear( sf::Color( 255, 255, 255 ) );
	GameWindow->Draw(backGroundSprite);

	Player1->draw();
	beetle->draw();

	for(vector<Block*>::iterator i= blockVec.begin();i!=blockVec.end();i++)//Iterator that goes through the vector of blocks
	{
		(*i)->draw();
	}
	for(vector<Gem*>::iterator i= gemVec.begin();i!=gemVec.end();i++)//Iterator that goes through the vector of GEMS
	{
		(*i)->draw();
	}

	exit->draw();

	headsUpDisplay();
	GameWindow->Display();
	return;//Initialise sprites and draw them.
}

void Game::getinput()
{
	sf::Event userEvent;
	while (GameWindow->GetEvent(userEvent))
	{
	
		if (((userEvent.Type == sf::Event::KeyReleased) && (userEvent.Key.Code == sf::Key::P)) && (!paused))
		{
			paused=true;
			printf("Paused");
		}
		if ((userEvent.Type == sf::Event::KeyReleased) && (userEvent.Key.Code == sf::Key::Return))
		{
			paused=false;
			printf("unpaused");
		}
	if ((userEvent.Type == sf::Event::KeyPressed) && (userEvent.Key.Code == sf::Key::Up))
		{
			
		}
	if ((userEvent.Type == sf::Event::KeyReleased) && (userEvent.Key.Code == sf::Key::Down))
		{
			
		}
	}
	return;//Handle Input
}

void Game::update(sf::RenderWindow* window)
{	
	if(Clock.GetElapsedTime() > 10.F / FRAME_RATE)
	{
	beetle->update();
	Player1->updatePlayer();
	Player1->updateBoxes();
	beetle->checkPlatforms( blockVec );

	if((Player1->collidesWithExit(exit)))
	{
		if(state==LEVEL_ONE)
		{
		scoreLevel1=Player1->getPlayerHealth();

		state = LEVEL_TWO;
		levelCleared=true;//clearLevel();
		}
	}
	
	if((Player1->collidesWithExit(exit)) && (level2Cleared==true))
		{
			//window->Close();
			//printf("TEST");
			state=GAME_OVER;
		}
	

	for(vector<Block*>::iterator it = blockVec.begin(); it != blockVec.end(); it++)
	{
		Player1->collidesWithBlock(*it);
	}

	for(vector<Gem*>::iterator it = gemVec.begin(); it != gemVec.end(); it++)
	{
		beetle->collidesWithGem(*it);
	}

	for(vector<Gem*>::iterator it = gemVec.begin(); it != gemVec.end();)
	{
		if( Player1->collidesWithGem(*it) )
		{
			delete (*it);
			it = gemVec.erase(it);
			continue;
		}
		++it;
	}

	if(Player1->playerHealth <0)
	{
		if(state==LEVEL_ONE)
		{
		clearLevel();
		LoadLevel(window,"level.dat");
		levelLoaded=false;
		state=LEVEL_ONE;
		}

		else if(state==LEVEL_TWO)
		{
		clearLevel();
		LoadLevel(window,"level2.dat");
		levelLoaded=false;
		state=LEVEL_TWO;
		}
		playerLives -=1;
		cout << "PLAYER LIVES " << playerLives <<  endl;
	}

	if(Player1->collidesWithBeetle(beetle))
	{
		if(state==LEVEL_ONE)
		{
		clearLevel();
		LoadLevel(window,"level.dat");
		levelLoaded=false;
		state=LEVEL_ONE;
		}
	
		else if(state==LEVEL_TWO)
		{
		clearLevel();
		LoadLevel(window,"level2.dat");
		levelLoaded=false;
		state=LEVEL_TWO;
		}
		playerLives -=1;
		cout << "player LIVES : " << playerLives << endl;
	}

	if(playerLives==0)
	{
		state=GAME_OVER;
	}

	Player1->setCollisions();
	Player1->attacked(beetle);
	getinput();
	}
	return;
}

void Game::play(sf::RenderWindow* window) //This should be caled in MAIN in a loop while the app is open.
{
	cout<<playerLives<< endl;
	getinput();
	while(!paused)
	{
	draw(window);
	update(window);
	
	}
}

void Game::clearLevel()
{
	bool cleared = false;

	if(cleared==false);
	{
	for( vector<Block*>::iterator i = blockVec.begin(); i != blockVec.end(); )
	{
		delete (*i);
		i = blockVec.erase( i );
	}

	for( vector<Gem*>::iterator i = gemVec.begin(); i != gemVec.end(); )
	{
		delete (*i);
		i = gemVec.erase( i );
	}

	delete exit;
	delete beetle;

	if(gameOver)
	// if game over or complete
	{
		delete Player1;
		Player1=nullptr;
	}

	}
	levelCleared=false;
}

void Game::setGameState(gameState GameState)
{
	state = GameState;
}

int Game::getPlayerLives()
{
	return playerLives;
}

	
void Game::headsUpDisplay()
{

	stringstream healthSS, livesSS, pauseSS;

	sf::String health;
	sf::String lives;
	sf::String pauseStr;


	int playerHealth = Player1->getPlayerHealth();
	healthSS << "Health: " << playerHealth;
	health.SetText(healthSS.str());
	health.SetSize(25);
	health.SetPosition(100,0);
	//health.SetColor(sf::Color(30,0,0,0));
	

	livesSS << "Lives: " << playerLives;
	lives.SetText(livesSS.str());
	lives.SetSize(25);
	lives.SetPosition(0,0);
	
	
	pauseSS << "PAUSED";
	pauseStr.SetText(pauseSS.str());
	pauseStr.SetSize(70);
	pauseStr.SetPosition(GameWindow->GetWidth() / 3, GameWindow->GetHeight() / 3 );

	if(paused)
	{
		GameWindow->Draw(pauseStr);
	}
	GameWindow->Draw(health);
	GameWindow->Draw(lives);

}

void Game::endGame(sf::RenderWindow* window)
{
	sf::Image gameOver;
	sf::Sprite gameOverSprite;

	gameOver.LoadFromFile("images/gameOver.png");
	gameOverSprite.SetImage(gameOver);
	scoreLevel2= Player1->getPlayerHealth();
	finalScore = scoreLevel1 + scoreLevel2;


	for(int i = 0;i<10;i++)
	{
	window->Clear();
	window->Draw(gameOverSprite);
	window->Display();
	}
	cout << "Your Final Score was : " << finalScore << endl;
	system("pause");
	
}
