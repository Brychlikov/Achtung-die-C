//
// Created by brych on 05.01.19.
//

#ifndef HELLOSFML_POWERUP_H
#define HELLOSFML_POWERUP_H


#include <SFML/Graphics.hpp>
#include "Effect.h"

class PowerUp {
private:
    sf::Vector2f position;
public:
    const sf::Vector2f &getPosition() const;

private:
    sf::CircleShape shape;
    sf::Sprite sprite;
public:
    const sf::CircleShape &getShape() const;

private:

    bool pickedUp = false;
public:
    bool isPickedUp() const;

    void setPickedUp(bool pickedUp);

private:
    Effect &effect;

    int radius = 20;
public:
    int getRadius() const;

public:
    PowerUp(Effect &effect, sf::Vector2f position);
    PowerUp(Effect &effect, sf::Vector2f position, sf::Texture texture);
    void setPosition(sf::Vector2f pos);
    void setRadius(int radius);

    void pick_up(Head * player);
};


#endif //HELLOSFML_POWERUP_H
