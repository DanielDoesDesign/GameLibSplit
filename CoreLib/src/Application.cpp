#include <iostream>
#include "Application.h"
#include "Config.h"
#include "Utility.h"
#include "State.h"
#include "StateIdent.h"

#include "DefaultState.h"
#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
: mWindow(nullptr)
, mTextures(nullptr)
, mFonts(nullptr)
, mStatisticsText(nullptr)
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{}

void Application::setContext(State::Context context)
{
	mContext = context;
	mWindow = context.window;
	mTextures = context.textures;
	mFonts = context.fonts;

	//std::cout << "CORE: mContext address:" << mContext << std::endl;
	std::cout << "CORE: mWindow: " << mWindow << std::endl;
	std::cout << "CORE: mTextures: " << mTextures << std::endl;
	std::cout << "CORE: mFonts: " << mFonts << std::endl;

	//Initialize StateStack after context is set
	mStateStack = std::make_unique<StateStack>(mContext);

	std::cout << "CORE: StateStack: " << mStateStack.get() << std::endl;
	std::cout << "CORE: SS Size: " << mStateStack->getSize() << std::endl;


	if (!mContext.window) {
        std::cerr << "CORE: Error: Null window in Application context!" << std::endl;
    }
	else
	{
		std::cout << "CORE: Window Context Pointer:" << context.window << std::endl;
	}

	registerStates();
	//why is this needed?
	mWindow->setKeyRepeatEnabled(false);
	std::cout << "CORE: Load Font\n";
	mFonts->load(Fonts::Main, "Media/Sansation.ttf");

	mTextures->load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

	std::cout << "CORE: Set stats\n";
	mStatisticsText = std::make_unique<sf::Text>(mFonts->get(Fonts::Main));
    mStatisticsText->setPosition({10.f, 10.f});
    mStatisticsText->setCharacterSize(16);

	registerStates();
	mStateStack->pushState(States::Title);
	std::cout << "CORE: SS Size: " << mStateStack->getSize() << std::endl;
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    std::cout << "CORE: Loop Init\n";

		//MAIN LOOP
    while (mWindow->isOpen())
    {
	//	std::cout << "Main Loop Started\n";

        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);

			if(mStateStack->isEmpty())
			std::cout << "CORE: No more states" << std::endl;
				mWindow->close();
        }
        updateStatistics(dt);
        render();
    }
}

void Application::processInput()
{
    while (const std::optional<sf::Event>& event = mWindow->pollEvent())
    {
		if (event){
			mStateStack->handleEvent(*event);
		}

		if (event->is<sf::Event::Closed>())
		{
			mWindow->close();
		}

	}
}


void Application::update(sf::Time dt)
{
	mStateStack->update(dt);
}

void Application::render()
{
   	mWindow->clear();
	
	mStateStack->draw();

	mWindow->setView(mWindow->getDefaultView());
	mWindow->draw(*mStatisticsText);
	mWindow->display();

}

void Application::updateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText->setString(
            "FPS = " + toString(mStatisticsNumFrames));
        
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Application::registerStates() {
    mStateStack->registerState<DefaultState>(States::Title);
}