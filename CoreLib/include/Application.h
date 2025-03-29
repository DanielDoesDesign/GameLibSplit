#ifndef APP_H
#define APP_H

#include "ResourceHolder.h"
#include "ResourceIdent.h"
#include "PlayerBase.h"
#include "StateStack.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class Application
{
    public:
                        	Application();
		virtual 			~Application() = default;

		void				setContext(State::Context context); // Dependency Injection method
        void                run();

	protected:
		virtual void 		registerStates();  // Must be implemented by the game

		void				processInput();
        void                update(sf::Time dt);
        void                render();
        void                updateStatistics(sf::Time dt);

		sf::RenderWindow*       mWindow;
		TextureHolder*			mTextures;
		FontHolder*				mFonts;

		public:
		State::Context 			mContext;
		std::unique_ptr<StateStack> mStateStack;

    private:
        static const sf::Time   TimePerFrame;

    	std::unique_ptr<sf::Text> mStatisticsText;
        sf::Time                mStatisticsUpdateTime;
        std::size_t             mStatisticsNumFrames;
};

#endif // BOOK_GAME_HPP