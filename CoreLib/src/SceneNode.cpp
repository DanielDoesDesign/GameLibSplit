
#include "SceneNode.h"
#include "Command.h"

#include <algorithm>
#include <cassert>

#include <iostream>

SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{
}

// Recursive function to print the scene graph
void SceneNode::printSceneGraph(int indent) const{
	std::cout << "SCENE GRAPH:";
    // Indentation for visual hierarchy
    for (int i = 0; i < indent; ++i) {
        std::cout << "  "; // Two spaces for each indent level
    }

    // Output the current node's details
	std::cout << "Name: " << getName();
	std::cout << " Cat: " << getCategory();
	//std::cout << " Type: " << typeid(this).name(); 
	std::cout << " Mem: " << this << "\n";

    //std::cout << " Pos: " << getPosition().x << ", " << getPosition().y;
   

    
	// Recursively print child nodes
    for (const auto& child : mChildren) {
		child->printSceneGraph(indent + 1); // Increase indentation for children
    }
}

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    //lambda expression. returns true if elements pointer p.get is equal
    //to the address of the wanted node
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
    [&] (Ptr& p) -> bool { return p.get() == &node; });
    //STL algo std::find_if() returns an iterator to the found element

    //check for validity
    assert(found != mChildren.end());

    //move the found node out of the container into variable
    Ptr result = std::move(*found);

    //set nodes parent pointer to nullptr
    result->mParent = nullptr;
    //erase the empty element from the container
    mChildren.erase(found);
    //return smart pointer containing the detached node
    return result;
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
    //do nothing
}

void SceneNode::updateChildren(sf::Time dt)
{
    for (const Ptr& child : mChildren)
    {
        child->update(dt);
    }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //do nothing
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Ptr& child : mChildren)
    {
        child->draw(target, states);
    }
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
    //set transform to an init Ident Matrix
    sf::Transform transform = sf::Transform::Identity;

    //as long as node hasnt reached the root node, 
    //change node to be its own parent (move up hierachy)
    for (const SceneNode* node = this;
        node != nullptr; node = node->mParent){
    //multiply this node's transform with the accumilating total (local variable)
    transform = node->getTransform() * transform;}
    
    return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	//std::cout << "Node Category: " << getCategory() << " Command Category: " << 
	//command.category << " Match: " << (getCategory() & command.category) << "\n";

	if (command.category & getCategory())
	{
		//std::cout << "Executing command on node: " << typeid(*this).name() << std::endl;
		command.action(*this, dt);
	}
	//Command children
	for (const auto& child : mChildren)
	{
		child->onCommand(command, dt);
	}
}

unsigned int SceneNode::getCategory() const
{
	if (mParent == nullptr)
	{
	return Category::Root;
	}
	else
	return Category::Scene;
}

std::string SceneNode::getName() const
{
	return "SceneNode";
}