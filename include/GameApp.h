#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "Application.h"
#include "StateStack.h"
#include "ResourceHolder.h"

class GameApp {
public:
    		GameApp();
	void	run();

private:
	void createContext();
    void registerStates();
	void loadResources(); // Method to load textures

	sf::RenderWindow 		mWindow; // Assume you're using SFML's RenderWindow
	TextureHolder			mTextures;
	FontHolder				mFonts;

    StateStack 				mStateStack;
	State::Context 			mContext;
	Application 			mApplication; // containing Application instead of inheritence

};

#endif // GAMEAPPLICATION_H
