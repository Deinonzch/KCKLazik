#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>

class Console
{
    public:
        Console(sf::RenderWindow * window);
        void draw();
        void setOutput(sf::String s);
        sf::String getCommand();
        void setCommand(sf::String s);
    protected:
    private:
        sf::RenderWindow * window;
        sf::Font courier;
        sf::Text t1;
        sf::Text t2;
        sf::Text t3;
        sf::Text t4;
        sf::Text prompt;
};

#endif // CONSOLE_H
