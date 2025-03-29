#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include "SFML/Window/Event.hpp"
#include "CommandQueue.h"
#include <map>

class CommandQueue;

class PlayerBase
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown
	};

											PlayerBase();
	virtual 								~PlayerBase() = default;

	virtual void							handleEvent(const sf::Event& event,
												CommandQueue& commands) = 0;
	virtual void							handleRealtimeInput(CommandQueue& commands) = 0;

};


#endif //PLAYER_H