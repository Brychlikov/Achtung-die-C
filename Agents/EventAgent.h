//
// Created by brych on 31.12.18.
//
#include "Agent.h"
#include <SFML/Window.hpp>

#ifndef HELLOSFML_EVENTAGENT_H
#define HELLOSFML_EVENTAGENT_H

class EventWrapper{
private:
    bool keyboardUsed;
    union{
        sf::Keyboard::Key keyLeft;
        sf::Event::JoystickButtonEvent padRight;
    };
    union{
        sf::Keyboard::Key keyRight;
        sf::Event::JoystickButtonEvent padLeft;
    };

public:
    EventWrapper(sf::Keyboard::Key left, sf::Keyboard::Key right);
    EventWrapper(sf::Event::JoystickButtonEvent left, sf::Event::JoystickButtonEvent right);

    int direction(sf::Event event);

};


class EventAgent: public Agent {
private:
    bool keyboardUsed;
    union {
        sf::Keyboard::Key leftKeyboard;
        sf::Event::JoystickButtonEvent leftGamepad;
    };
    union {
        sf::Keyboard::Key rightKeyboard;
        sf::Event::JoystickButtonEvent rightGamepad;
    };

    bool goingRight = false;
    bool goingLeft = false;
public:
    EventAgent(Head * player, std::vector <Head *> enemies, sf::Keyboard::Key left, sf::Keyboard::Key right);
    EventAgent(Head * player, std::vector <Head *> enemies, sf::Event::JoystickButtonEvent left, sf::Event::JoystickButtonEvent right);
    bool isGoingRight();

    void setGoingRight(bool goingRight);

    bool isGoingLeft();

    void setGoingLeft(bool goingLeft);

    void update(sf::Event event);

    int decision();


};


#endif //HELLOSFML_EVENTAGENT_H
