//
// Created by brych on 31.12.18.
//
#include <SFML/Graphics.hpp>
#include "../Head.h"
#include <vector>

#ifndef HELLOSFML_AGENT_H
#define HELLOSFML_AGENT_H


class Agent {
protected:
    Head * player;
    std::vector <Head *> enemies;

public:
    Agent(Head * player, std::vector <Head *> enemies);
    void update();
    int decision();

    void applyDecision();

};


#endif //HELLOSFML_AGENT_H
