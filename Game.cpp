//
// Created by brych on 31.12.18.
//

#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <math.h>


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

void Game::addPlayer(Head *player, sf::Event::JoystickButtonEvent left, sf::Event::JoystickButtonEvent right) {
    // TODO make it into template
    player->setParent(this);
    for(auto other: players){
        player->addEnemy(other);
        other->addEnemy(player);
    }
    EventAgent agent(player, player->getEnemies(), left, right);
    eventListeners.push_back(agent);

    players.push_back(player);

}

void Game::addPowerUp(Effect &effect, sf::Vector2f position) {
    auto temp = new PowerUp(effect, position);
    powerUps.push_back(temp);
}

void Game::addPowerUp(Effect &effect, sf::Vector2f position, sf::Texture texture) {
    auto temp = new PowerUp(effect, position, texture);
    powerUps.push_back(temp);
}

float distance(sf::Vector2f d1, sf::Vector2f d2){
    float sq1 = (d1.x - d2.x) * (d1.x - d2.x);
    float sq2 = (d1.y - d2.y) * (d1.y - d2.y);
    return sqrtf(sq1 + sq2);
}

void Game::handlePowerUps() {
    for(auto player: players){
        for(auto pickup: powerUps){
            if(pickup->isPickedUp())
                continue;
            float dist = distance(pickup->getPosition(), player->getPosition());
            std::cout << "Dist: " << dist << std::endl;
            if(dist < player->getWidth() + pickup->getRadius()){
                std::cout << "!!!!!!!!!!!!!!!!picked up!!!!!!!!!!!!!!!!" << std::endl;
                pickup->pick_up(player);
                pickup->setPickedUp(true);
            }
        }
    }


}

void Game::handleEvents() {
    sf::Event event;
    while(window->pollEvent(event)){
        if (event.type == sf::Event::JoystickButtonPressed)
            std::cout << "ID: " << event.joystickButton.joystickId << "BTN:  " << event.joystickButton.button << std::endl;
        if(event.type == sf::Event::Closed)
            window->close();

        if(event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Space){
                auto test = new SpeedEffect(players[0], 3, 5);
                players[0]->addEffect(test);
            }
        }

        for(auto &listener: eventListeners){
            listener.update(event);
        }
    }

    for(auto listener: eventListeners){
        listener.applyDecision();
    }
}

void Game::updateLogic() {

    //capture image of current game state. Used for collision detection
    sf::Vector2u windowSize = window->getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(*window);
    sf::Image currentState = texture.copyToImage();

    for(auto player: players){
        player->update(currentState);
    }

    handlePowerUps();

}

void Game::drawFrame() {
    window->clear(settings.backgroundColor);
    for(auto player: players){
        window->draw(player->getShape());
        window->draw(player->getHeadShape());
    }

    for(auto pickUp: powerUps){
        window->draw(pickUp->getShape());
    }

//    sf::RectangleShape mapRect;
//    mapRect.setPosition(0, 0);
//    mapRect.setSize(sf::Vector2f(settings.width, settings.height));
//    mapRect.setFillColor(sf::Color(0, 0, 100, 100));
//
//    window->draw(mapRect);

    window->display();
}
