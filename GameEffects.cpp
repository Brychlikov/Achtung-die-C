//
// Created by brych on 05.01.19.
//

#include "GameEffects.h"

SpeedEffect::SpeedEffect(Head * target, sf::Time length, float speed_delta): Effect(target, length){
    this->speed_delta = speed_delta;
    start();
}
SpeedEffect::SpeedEffect(Head * target, float length, float speed_delta): Effect(target, length){
    this->speed_delta = speed_delta;
    start();
}

SpeedEffect::SpeedEffect(float length, float speed_delta): Effect(length){
    this->speed_delta = speed_delta;
}

void SpeedEffect::setTarget(Head *target) {
    clock.restart();
    this->target = target;
    start();
}

void SpeedEffect::start() {
    target->setSpeed(target->getSpeed() + speed_delta);
}

void SpeedEffect::end() {
    target->setSpeed(target->getSpeed() - speed_delta);
}

bool SpeedEffect::update() {
    sf::Time time = clock.getElapsedTime();
    if(time >= length){
        end();
        return true;
    }
    else
        return false;
}
