//
// Created by brych on 31.12.18.
//
#include "Agent.h"
#include <SFML/Window.hpp>

#ifndef HELLOSFML_EVENTAGENT_H
#define HELLOSFML_EVENTAGENT_H

class EventWrapper{
    struct joystickKey{
        int joystickNum;
        int keyNum;
    };
private:
    union{
        sf::Keyboard::Key keyLeft;
        joystickKey joystickLeft;
    };
    bool leftKeyboardUsed;
    union{
        sf::Keyboard::Key keyLeft;
        joystickKey joystickLeft;
    };
    bool rightKeyboardUsed;

};


class EventAgent: public Agent {
private:
    sf::Keyboard::Key leftEvent;
    sf::Keyboard::Key rightEvent;

    bool goingRight = false;
    bool goingLeft = false;
public:
    EventAgent(Head * player, std::vector <Head *> enemies, sf::Keyboard::Key left, sf::Keyboard::Key right);
    bool isGoingRight();

    void setGoingRight(bool goingRight);

    bool isGoingLeft();

    void setGoingLeft(bool goingLeft);

    void update(sf::Event event);

    int decision();


};


#endif //HELLOSFML_EVENTAGENT_H
