#ifndef WORLD_H
#define WORLD_H

#include "ResourceHolder.h"
#include "ResourceIdent.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include "Command.h"

#include <iostream>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

// Forward declaration
namespace sf
{
	class RenderWindow;
	class RenderTexture;
}

class World
{
	public:
		explicit 		World(sf::RenderWindow& window, const sf::Vector2u& nativeWindowSize);
		void			update(sf::Time dt);
		void			draw();

		CommandQueue&	getCommandQueue();

	private:
		void			loadTextures();
		void			buildScene();
		void			adaptPlayerPosition();
		void			adaptPlayerVelcity();

		

	private:
		enum Layer
		{
			Background,
			Air,
			LayerCount 
		};

	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		sf::Vector2u 						mNativeWindowSize; // Store the native window size
		sf::RenderTexture 					mRenderTexture;


		SceneNode							mSceneGraph; //(root of)
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		float								mScrollSpeed;
		Aircraft*							mPlayerAircraft;
};

#endif //WORLD_H