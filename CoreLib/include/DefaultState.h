#ifndef DEFAULTSTATE_H
#define DEFAULTSTATE_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class DefaultState : public State
{
public:
						DefaultState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	bool				mShowText;
	sf::Time			mTextEffectTime;
};

#endif // DEFAULTSTATE_H