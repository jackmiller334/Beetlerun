#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


void splashScreen(sf::RenderWindow* window);

int main()
{
	unsigned int width=800;  // Width of the game window
	unsigned int height=600;
	
	sf::RenderWindow app(sf::VideoMode(width, height), "BEETLE RUN"); // Create main window for the game to go in
	 // Open it from an audio file




	sf::Music music;
if (!music.OpenFromFile("music/gamemusic.ogg"))
 {
 }

	music.SetLoop(true);
	music.SetVolume(45);
	music.SetPitch(1);
	music.Play();//Play the Melody I made :3

	Game *game = new Game( &app );
	app.SetFramerateLimit(30);
	
	splashScreen(&app);

	printf("GAME IS RUNNING");
	cout << " " << endl;

	sf::Event Event;

	while( app.IsOpened())
	{	
		
		game->play(&app);
		
	
		 while (app.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                app.Close();

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
               app.Close();
		
		}
		//else break;
	}

	delete game;
	game = nullptr;

	//system("pause");
	return 0;
}


void splashScreen(sf::RenderWindow* window)
{
	sf::Image splashImage;
	sf::Sprite splashSprite;
	splashImage.LoadFromFile("images/splash.png");
	splashSprite.SetImage(splashImage);

	sf::Clock clock;
	//for(clock.GetElapsedTime(); clock > 2) 
	//!window->GetInput().IsKeyDown( sf::Key::Left))
	
	//for(clock.GetElapsedTime()
	for(int i = 0;i<200;i++)
	{
	window->Clear();
	window->Draw(splashSprite);
	window->Display();
	}
}