//
// Created by brych on 31.12.18.
//

#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H

#include <SFML/Graphics.hpp>
#include "Agents/EventAgent.h"
#include "Head.h"
#include "Effect.h"
#include "GameEffects.h"
#include <vector>

struct gameSettings{
    int width;
    int height;

    int ghostFrames;
    int ghostProportion;

    double radiansPerTick;
    float defaultSpeed;
    int defaultWidth;

    sf::Color backgroundColor;
};

class Game {
private:
    float speed;
    std::vector <Head *> players;
    std::vector <EventAgent> eventListeners;
    gameSettings settings;

    sf::RenderWindow * window;

public:
    gameSettings getSettings();
    Game(gameSettings settings, sf::RenderWindow * window);
    void addPlayer(Head * player, sf::Keyboard::Key left, sf::Keyboard::Key right);
    void addPlayer(Head * player, sf::Event::JoystickButtonEvent left, sf::Event::JoystickButtonEvent right);

    void handleEvents();
    void updateLogic();
    void drawFrame();


};


#endif //HELLOSFML_GAME_H
