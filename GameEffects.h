//
// Created by brych on 05.01.19.
//

#ifndef HELLOSFML_GAMEEFFECTS_H
#define HELLOSFML_GAMEEFFECTS_H

#include "Effect.h"


class SpeedEffect: virtual public Effect {
private:
    float speed_delta;
protected:
    void start() override;
    void end() override;

public:
    SpeedEffect(Head * target, sf::Time length, float speed_delta);
    SpeedEffect(Head * target, float length, float speed_delta);
    SpeedEffect(float length, float speed_delta);
    void setTarget(Head * target);
    bool update();
};


#endif //HELLOSFML_GAMEEFFECTS_H
