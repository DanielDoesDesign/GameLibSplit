#include "World.h"

#include "SFML/Graphics/RenderWindow.hpp"

#include <algorithm>
#include <cmath>

World::World(sf::RenderWindow& window, const sf::Vector2u& nativeWindowSize)
: mWindow(window)
, mNativeWindowSize(nativeWindowSize)
, mWorldView({0,0}, (sf::Vector2f)nativeWindowSize)
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mWorldBounds({0.f,0.f},{mWorldView.getSize().x,10000.f})
, mSpawnPosition({mWorldView.getSize().x / 2.f, mWorldBounds.size.y - (mWorldView.getSize().y / 2.f)})
, mScrollSpeed(-40.f)
, mPlayerAircraft(nullptr)
{
	mRenderTexture.resize(nativeWindowSize);

	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

};

void World::update(sf::Time dt)
{
	mWorldView.move({0.f, mScrollSpeed * dt.asSeconds()});
	mPlayerAircraft->setVelocity({0.f, 0.f});

	//Forwards commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(),dt);

	adaptPlayerVelcity();

	//Regular update step
	mSceneGraph.update(dt);

	adaptPlayerPosition();
}

extern float gScaleFactor;

void World::draw()
{
    mRenderTexture.clear();
    mRenderTexture.setView(mWorldView);
    mRenderTexture.draw(mSceneGraph); // Draw your scene graph
    mRenderTexture.display(); // Display the texture

	// Then, draw the RenderTexture to the main window
	sf::Sprite renderSprite(mRenderTexture.getTexture());

	renderSprite.setScale({gScaleFactor, gScaleFactor}); // Scale the entire RenderTexture sprite

    mWindow.draw(renderSprite);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}

void World::buildScene()
{
	//add layers to the root scene node as children
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		
		//Attach layer to root
		mSceneGraph.attachChild(std::move(layer));
	}

	//get background texture
	std::cout << "Setting background texture!\n";
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);


	texture.setRepeated(true);

	//create background
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	//backgroundSprite->setScale({0.5f, 0.5f});
	backgroundSprite->setPosition({mWorldBounds.position.x,mWorldBounds.position.y});
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	//load airplanes 
	std::cout << "Loading Planes!\n";
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	//std::unique_ptr<Aircraft> leader = std::make_unique<Aircraft>(Aircraft::Eagle, mTextures);
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	//mPlayerAircraft->setVelocity(0.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	//translates into worldspace rect
	sf::FloatRect viewBounds(
		mWorldView.getCenter() - mWorldView.getSize() / 2.f, 
		mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.position.x + borderDistance);
	position.x = std::min(position.x, viewBounds.position.x + viewBounds.size.x - borderDistance);
	position.y = std::max(position.y, viewBounds.position.y + borderDistance);
	position.y = std::min(position.y, viewBounds.position.y + viewBounds.size.y - borderDistance);
	mPlayerAircraft->setPosition(position);
}


void World::adaptPlayerVelcity()
{
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

	mPlayerAircraft->accelerate(0.f,mScrollSpeed);
}

