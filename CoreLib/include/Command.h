#ifndef COMMAND_H
#define COMMAND_H

#include "SFML/System/Time.hpp"
#include "SceneNode.h"
#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
													Command();

	std::function<void(SceneNode&, sf::Time)>		action;
	unsigned int									category;
};

/*Since we often work on entities that are classes derived from SceneNode, the constant 
need for downcasts is annoying. It would be much more user friendly if we could 
directly create a function with the signature void(Aircraft& aircraft, sf::Time 
dt) instead. This is possible, if we provide a small adapter derivedAction() that 
takes a function on a derived class such as Aircraft and converts it to a function on 
the SceneNode base class. We create a lambda expression, inside which we invoke 
the original function fn on the derived class, passing a downcast argument to it. An 
additional assertion checks in the debug mode that the conversion is safe, which 
is extremely helpful to avoid bugs. */

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	//lambada [=] capture list meaning that variables referenced from its body 
	//such as the variable fn) are copied from the surrounding scope
	return [=] (SceneNode& node, sf::Time dt)
	{
		//Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
	
		//Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif //COMMAND_H