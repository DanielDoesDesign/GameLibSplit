#ifndef STATE_H
#define STATE_H

#include "StateIdent.h"
#include "ResourceIdent.h"

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include <memory>

namespace sf
{
	class RenderWindow;
}

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context { 
		Context() : window(nullptr), textures(nullptr), fonts(nullptr) {} // Default constructore				
		
		Context(sf::RenderWindow& win, TextureHolder& tex, FontHolder& fnt)
		: window(&win), textures(&tex), fonts(&fnt){}

		void setWindow(sf::RenderWindow& win) {window = &win;}
		void setTextures(TextureHolder& tex) { textures = &tex;}
		void setFonts(FontHolder& fnt) {fonts = &fnt;}

		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts; 
	};

public:
	explicit				State(StateStack& stack, Context context);
	virtual			~State();

	virtual void	draw() = 0;
	virtual bool	update(sf::Time dt) = 0;
	virtual bool	handleEvent(const sf::Event& event) = 0;

protected:
	void			requestStackPush(States::ID stateID);
	void			requestStackPop();
	void			requestStateClear();

	Context			getContext() const;

private:
	StateStack*		mStack;
	Context			mContext;
};

#endif //STATE_H