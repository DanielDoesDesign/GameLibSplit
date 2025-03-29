#include "GameApp.h"
//#include "../CoreLib/include/Config.h" (implement later time)

//#include "GameState.h"
#include "TitleState.h"
#include "PauseState.h"
#include "Application.h"

 // Original window size
 sf::Vector2u gWindowSize(640, 480);

 // Global scaleFactor
float gScaleFactor = 1.0f; // Modify this to change the scale

 // Scaled window size
 sf::Vector2u scaledWindowSize(static_cast<unsigned int>(gWindowSize.x * gScaleFactor),
                               static_cast<unsigned int>(gWindowSize.y * gScaleFactor));


// GameApplication.cpp
GameApp::GameApp()
: mWindow(sf::VideoMode({scaledWindowSize.x, scaledWindowSize.y}), "SFML GAME", sf::Style::Close, sf::State::Windowed)
, mStateStack(mContext)
{
	std::cout << "GAME: Instance Created" << std::endl;

	createContext();
	mApplication.setContext(mContext);

	// Ensure StateStack is created before registering states
	mApplication.mStateStack = std::make_unique<StateStack>(mContext);

	registerStates();

	std::cout << "GAME: Window Pointer: " << &mWindow << std::endl;
}

void GameApp::createContext(){
	std::cout << "GAME: Creating Context" << std::endl;

	mContext.setWindow(mWindow);
	mContext.setTextures(mTextures);
	mContext.setFonts(mFonts);
}

void GameApp::registerStates() {
   // mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<PauseState>(States::Pause);
}

void GameApp::run()
{
	mApplication.run();
}
