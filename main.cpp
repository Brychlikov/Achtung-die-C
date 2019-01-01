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

    gameSettings mySettings;
    mySettings.backgroundColor = sf::Color::Black;
    mySettings.height = 800;
    mySettings.width = 800;
    mySettings.ghostFrames = 30;
    mySettings.ghostProportion = 3;

    Game mGame(mySettings, &window);


    Head myHead(100, 200, 5, 3, M_PI/10);
    myHead.setParent(&mGame);
    Head hania(300, 200, 5, 3, M_PI - M_PI/10);
    hania.setParent(&mGame);

    hania.setColor(sf::Color(255, 100, 50));

    myHead.addEnemy(&hania);
    hania.addEnemy(&myHead);

    auto test1 = std::addressof(myHead);
    auto test2 = std::addressof(hania.getEnemies()[0]);

    EventAgent keyAgent1(&myHead, hania.getEnemies(), sf::Keyboard::A, sf::Keyboard::D);
    EventAgent keyAgent2(&hania, myHead.getEnemies(), sf::Keyboard::Left, sf::Keyboard::Right);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            keyAgent1.update(event);
            keyAgent2.update(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        myHead.turn(M_PI/30 * keyAgent1.decision());
        hania.turn(M_PI/30 * keyAgent2.decision());

//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//            myHead.turn(3.1415 / 60 * -1);
//        }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//            myHead.turn(3.1415 / 60);
//        }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
//            myHead.setGhost(!myHead.isGhost());
//        }

        sf::Vector2u windowSize = window.getSize();
        sf::Texture texture;
        texture.create(windowSize.x, windowSize.y);
        texture.update(window);
        sf::Image currentState = texture.copyToImage();

        myHead.update(currentState);
        hania.update(currentState);

        sf::RectangleShape mapRect;
        mapRect.setPosition(0, 0);
        mapRect.setSize(sf::Vector2f(800, 800));
        mapRect.setFillColor(sf::Color(0, 0, 100, 100));


        window.clear(sf::Color::Black);
        window.draw(mapRect);
        window.draw(myHead.getShape());
        window.draw(myHead.getHeadShape());
        window.draw(hania.getShape());
        window.draw(hania.getHeadShape());

        window.display();

    }
    return 0;
}