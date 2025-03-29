//Game Configuration setup using preprocessor if's
//so that I dont have to find variables to change

//TODO: Change to a more elegant solution


#define IS_FULLSCREEN 0
 



//Hide



#if IS_FULLSCREEN == 1
sf::State isFullscreen = sf::State::Fullscreen;
#else
sf::State isFullscreen = sf::State::Windowed;
#endif