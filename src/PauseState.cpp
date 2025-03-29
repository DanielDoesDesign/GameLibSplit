#include "PauseState.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

PauseState::PauseState(StateStack &stack, Context context)
: State(stack, context)
//, mBackgroundSprite()
, mPausedText(context.fonts->get(Fonts::Main))
, mInstructionText(context.fonts->get(Fonts::Main))
{
	sf::Vector2f viewSize = context.window->getView().getSize();

	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition({0.5f * viewSize.x, 0.4f * viewSize.y});

	mInstructionText.setString("(Press Backspace to return to the main menu)");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition({0.5f * viewSize.x, 0.6f * viewSize.y});
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0,0,0,180));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (!event.is<sf::Event::KeyPressed>())
		return false;

	if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				//Escape pressed, remove itself to return to the game
				requestStackPop();

			if(keyPressed->scancode == sf::Keyboard::Scancode::Backspace)
			{
				//Backspace pressed, remove itself to return to the game
				requestStateClear();
				//requestStackPush(States::Menu);
			}
		}
	
		return false;
}