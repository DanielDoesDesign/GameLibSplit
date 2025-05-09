#include <Aircraft.h>
#include <ResourceHolder.h>


Textures::ID toTextureID(Aircraft::Type type)
{
        switch (type)
        {
                case Aircraft::Eagle:
                        return Textures::Eagle;
                case Aircraft::Raptor:
                        return Textures::Raptor;
        }
        return Textures::Eagle; //fallthrough default
}

Aircraft::Aircraft(Type type, const TextureHolder& textures):
mType(type), 
mSprite(textures.get(toTextureID(type)))
{
   sf::FloatRect bounds = mSprite.getLocalBounds();
   mSprite.setOrigin(bounds.getCenter());
}

void Aircraft::drawCurrent(sf::RenderTarget& target, 
        sf::RenderStates states) const
{
   target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
	/*switch (mType)
	{
		case Eagle:
			return Category::PlayerAircraft;
		default:
			return Category::EnemyAircraft;
	}*/
	return Category::PlayerAircraft;
}

std::string Aircraft::getName() const
{
	return "Aircraft";
}