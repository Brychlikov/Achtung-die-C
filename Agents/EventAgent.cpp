//
// Created by brych on 31.12.18.
//

#include "EventAgent.h"
#include <SFML/Graphics.hpp>
#include <vector>

bool EventAgent::isGoingRight() {
    return goingRight;
}

void EventAgent::setGoingRight(bool goingRight) {
    EventAgent::goingRight = goingRight;
}

bool EventAgent::isGoingLeft() {
    return goingLeft;
}

void EventAgent::setGoingLeft(bool goingLeft) {
    EventAgent::goingLeft = goingLeft;
}

EventAgent::EventAgent(Head * player, std::vector <Head *> enemies, sf::Keyboard::Key left, sf::Keyboard::Key right): Agent(player, enemies) {
    leftEvent = left;
    rightEvent = right;
}

void EventAgent::update(sf::Event event) {
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == leftEvent){
            goingLeft = true;
        }
        else if(event.key.code == rightEvent){
            goingRight = true;
        }
    }
    else if(event.type == sf::Event::KeyReleased){
        if(event.key.code == leftEvent){
            goingLeft = false;
        }
        else if(event.key.code == rightEvent){
            goingRight = false;
        }
    }
}
int EventAgent::decision() {
    if(goingLeft == goingRight)
        return 0;
    else if(goingLeft)
        return -1;
    else // goingRight
        return 1;
}
