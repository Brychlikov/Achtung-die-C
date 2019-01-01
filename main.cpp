#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Agents/EventAgent.h"
#include "Game.h"
#include <cmath>
#include <iostream>
#include <chrono>

#include <memory>

std::vector <sf::RectangleShape> drawableHitboxes(std::vector<sf::FloatRect> &hitboxes){
    std::vector <sf::RectangleShape> result;
    for(auto box: hitboxes){
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(box.width, box.height));
        rect.setPosition(box.left, box.top);
        rect.setFillColor(sf::Color(255, 0, 100, 128));
        result.push_back(rect);
    }
    return result;
}

int main() {


    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
    window.setFramerateLimit(30);
    window.clear(sf::Color::Black);
    window.setKeyRepeatEnabled(false);

    gameSettings mySettings;
    mySettings.backgroundColor = sf::Color::Black;
    mySettings.height = 800;
    mySettings.width = 800;
    mySettings.ghostFrames = 30;
    mySettings.ghostProportion = 3;
    mySettings.radiansPerTick = M_PI/30;

    Game mGame(mySettings, &window);


    Head player1(200, 200, 5, 3, 0);
    player1.setColor(sf::Color::Green);
    Head player2(600, 600, 5, 3, M_PI);
    player2.setColor(sf::Color::Magenta);

    mGame.addPlayer(&player1, sf::Keyboard::Left, sf::Keyboard::Right);
    mGame.addPlayer(&player2, sf::Keyboard::A, sf::Keyboard::D);


    while (window.isOpen())
    {
        mGame.handleEvents();
        mGame.updateLogic();
        mGame.drawFrame();


    }
    return 0;
}