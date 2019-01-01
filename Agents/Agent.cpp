//
// Created by brych on 31.12.18.
//

#include "Agent.h"
#include "../Game.h"

Agent::Agent(Head * player, std::vector<Head *> enemies) {
    this->player = player;
    this->enemies = enemies;
}

int Agent::decision() {
    return 0;
}

void Agent::applyDecision() {
    this->player->turn(this->player->getParent()->getSettings().radiansPerTick * this->decision());
}
