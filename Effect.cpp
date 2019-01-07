//
// Created by brych on 05.01.19.
//

#include "Effect.h"

Effect::Effect(Head * target, sf::Time length) {
    this->length = length;
    clock = sf::Clock();
    this->target = target;
}
Effect::Effect(Head * target, float length) {
    this->length = sf::seconds(length);
    clock = sf::Clock();
    this->target = target;
}

Effect::Effect(float length) {
    this->length = sf::seconds(length);
}

void Effect::setTarget(Head *target) {
    this->target = target;
    clock = sf::Clock();
}

bool Effect::update() {
    if(clock.getElapsedTime() >= length){
        this->end();
        return true;
    }
    else
        return false;
}

