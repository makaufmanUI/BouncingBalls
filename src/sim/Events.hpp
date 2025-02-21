#include <SFML/Graphics.hpp>

namespace event
{


// Hanldes the event of closing the window
// @param window: the window to close
void CheckForClose(sf::RenderWindow& window)
{
    sf::Event e {};
    while (window.pollEvent(e))
        if (e.type == sf::Event::Closed)
            window.close();
}


}