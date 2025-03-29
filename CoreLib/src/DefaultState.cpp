#include "DefaultState.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>

DefaultState::DefaultState(StateStack& stack, Context context)
: State(stack, context)
, mText(context.fonts->get(Fonts::Main))
, mBackgroundSprite(context.textures->get(Textures::TitleScreen))
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	//mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("DEFAULT SCREEN");
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

void DefaultState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}

bool DefaultState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.2f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	return true;
}

bool DefaultState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.is<sf::Event::KeyPressed>())
	{
		requestStackPop();
		//requestStackPush(States::Game);
	}
	return false;
}
