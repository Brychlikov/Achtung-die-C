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
    keyboardUsed = true;
    leftKeyboard = left;
    rightKeyboard = right;
}

EventAgent::EventAgent(Head *player, std::vector<Head *> enemies, sf::Event::JoystickButtonEvent left,
                       sf::Event::JoystickButtonEvent right): Agent(player, enemies) {
    keyboardUsed = false;
    leftGamepad = left;
    rightGamepad = right;
}

void EventAgent::update(sf::Event event) {
    if(keyboardUsed) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == leftKeyboard) {
                goingLeft = true;
            } else if (event.key.code == rightKeyboard) {
                goingRight = true;
            }
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == leftKeyboard) {
                goingLeft = false;
            } else if (event.key.code == rightKeyboard) {
                goingRight = false;
            }
        }
    }
    else{
        if (event.type == sf::Event::JoystickButtonPressed){
            if (event.joystickButton.button == leftGamepad.button && event.joystickButton.joystickId == leftGamepad.joystickId)
                goingLeft = true;
            else if(event.joystickButton.button == rightGamepad.button && event.joystickButton.joystickId == rightGamepad.joystickId)
                goingRight = true;
        } else if (event.type == sf::Event::JoystickButtonReleased){
            if (event.joystickButton.button == leftGamepad.button && event.joystickButton.joystickId == leftGamepad.joystickId)
                goingLeft = false;
            else if(event.joystickButton.button == rightGamepad.button && event.joystickButton.joystickId == rightGamepad.joystickId)
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
