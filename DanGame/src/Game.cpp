#include "Core.h"
#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "SFML Window");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                //test
            }
        }

        window.clear();
        window.display();
    }
}