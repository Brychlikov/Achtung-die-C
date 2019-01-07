//
// Created by brych on 05.01.19.
//

#ifndef HELLOSFML_EFFECT_H
#define HELLOSFML_EFFECT_H


#include <SFML/System/Clock.hpp>
#include "Head.h"

class Effect {
protected:
    sf::Clock clock;
    Head * target;
    sf::Time length;
    virtual void start() {};
    virtual void end() {};
public:
    Effect(Head * target, sf::Time length);
    Effect(Head * target, float length);
    Effect(float length);

    virtual void setTarget(Head * target);

    virtual bool update();
};




#endif //HELLOSFML_EFFECT_H
