//
// Created by brych on 31.12.18.
//

#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"


Game::Game(gameSettings settings, sf::RenderWindow * window){
    this->settings = settings;
    this->window = window;
}
gameSettings Game::getSettings() {
    return settings;
}

void Game::addPlayer(Head *player, sf::Keyboard::Key left, sf::Keyboard::Key right) {
    player->setParent(this);
    for(auto other: players){
        player->addEnemy(other);
        other->addEnemy(player);
    }
    EventAgent agent(player, player->getEnemies(), left, right);
    eventListeners.push_back(agent);

    players.push_back(player);

}

void Game::handleEvents() {
    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed)
            window->close();

        for(auto &listener: eventListeners){
            listener.update(event);
        }
    }

    for(auto listener: eventListeners){
        listener.applyDecision();
    }
}

void Game::updateLogic() {

    sf::Vector2u windowSize = window->getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(*window);
    sf::Image currentState = texture.copyToImage();

    for(auto player: players){
        player->update(currentState);
    }

}

void Game::drawFrame() {
    window->clear(settings.backgroundColor);
    for(auto player: players){
        window->draw(player->getShape());
        window->draw(player->getHeadShape());
    }
//    sf::RectangleShape mapRect;
//    mapRect.setPosition(0, 0);
//    mapRect.setSize(sf::Vector2f(settings.width, settings.height));
//    mapRect.setFillColor(sf::Color(0, 0, 100, 100));
//
//    window->draw(mapRect);

    window->display();
}
