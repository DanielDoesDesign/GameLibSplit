#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SFML/Graphics/Sprite.hpp>
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
    public:
        explicit        		SpriteNode(const sf::Texture& texture);
                        		SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
		virtual std::string 	getName() const override;

    private:
        virtual void    		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite      		mSprite;  
};

#endif //SPRITENODE_H