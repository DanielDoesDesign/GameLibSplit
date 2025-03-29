#include "GameApp.h"
#include "Application.h"

#include <iostream>
#include <stdexcept>

int simLibOnly = 0;

int main()
{
	//mFonts.load(Fonts::Main, "Media/Sansation.ttf");
	//mStatisticsText = std::make_unique<sf::Text>(mFonts.get(Fonts::Main));

	if(simLibOnly)
	{
	   // Create a minimal window for the context
	   //sf::RenderWindow window(sf::VideoMode({800, 600}), "Application Window");
	   //TextureHolder textureHolder; // Assuming you have a default constructor
	   //FontHolder fontHolder;
	   //State::Context context(window, textureHolder, fontHolder);
	   // Create the Application instance and pass the context
	   Application app;
	   app.run();
	   std::cout << "Exiting NORMALLY" << std::endl;
	   return 0;
	}
	else
	{
		GameApp app;
		app.run();
		std::cout << "Exiting NORMALLY" << std::endl;
		return 0;
	}

/*
	try
	{
    Application app;

    app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
		*/
}




