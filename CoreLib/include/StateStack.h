#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.h"
#include "StateIdent.h"
#include "ResourceIdent.h"

#include "SFML/System/Time.hpp"

#include <vector>
#include <utility>
#include <functional>
#include <map>

//TODO: Find out what is the purpose of these declarations?
//Whats the difference than just including the library header?

//what is this namespace for? small fast?

#include <optional>

namespace sf
{
	class RenderWindow;
	class Event;
}

class StateStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				registerState(States::ID stateID);

	void				update(sf::Time dt);
	void				draw();
	void				handleEvent(const sf::Event& event);

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();

	bool				isEmpty() const;
	size_t				getSize() {return mStack.size();}

private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();

private:
	struct PendingChange
	{
		explicit		PendingChange(Action action, States::ID stateID = States::None);

		Action			action;
		States::ID		stateID;
	};

private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;
	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>> 	mFactories;

};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this] ()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

#endif //STATESTACK_H