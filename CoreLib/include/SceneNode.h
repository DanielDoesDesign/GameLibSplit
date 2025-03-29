#ifndef BOOK_SCENENODE_HPP
#define BOOK_SCENENODE_HPP

#include "Category.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>
#include <memory>
#include <string>

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;

    public:
								SceneNode();

        void					attachChild(Ptr child);
        Ptr						detachChild(const SceneNode& node);
  
        void                	update(sf::Time dt);
 
        sf::Transform       	getWorldTransform() const;
        sf::Vector2f        	getWorldPosition() const;

		void					onCommand(const Command& command, sf::Time dt);

		virtual unsigned int	getCategory() const;
		virtual std::string 	getName() const;

		void 					printSceneGraph(int indent = 0) const;

    private:
        virtual void        	updateCurrent(sf::Time dt);
        void                	updateChildren(sf::Time dt);
 
        virtual void        	draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void        	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent;

};

#endif // BOOK_SCENENODE_HPP

