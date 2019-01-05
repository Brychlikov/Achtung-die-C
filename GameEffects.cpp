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

void SpeedEffect::start() {
    target->setSpeed(target->getSpeed() + speed_delta);
}

void SpeedEffect::end() {
    target->setSpeed(target->getSpeed() - speed_delta);
}

bool SpeedEffect::update() {
    if(clock.getElapsedTime() >= length){
        end();
        return true;
    }
    else
        return false;
}
