#ifndef BOOK_RESOURCEIDENTIFIERS_HPP
#define BOOK_RESOURCEIDENTIFIERS_HPP

namespace sf
{
    class Texture;
	class Font;
}

namespace Textures
{
    enum ID
    {
        Eagle,
        Raptor,
		Desert,
		TitleScreen,
    };
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

//Forward declaration
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> 	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif //BOOK_RESOURCEIDENTIFIERS_HPP