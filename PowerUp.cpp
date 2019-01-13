//
// Created by brych on 05.01.19.
//

#include "PowerUp.h"

PowerUp::PowerUp(Effect &effect, sf::Vector2f position): effect(effect) {
    this ->effect = effect;
    this->position = position;
    shape = sf::CircleShape(radius);
    shape.setPosition(position - sf::Vector2f(radius, radius));
    shape.setFillColor(sf::Color::Cyan);
    usingTexture = false;
}

PowerUp::PowerUp(Effect &effect, sf::Vector2f position, sf::Texture &texture): effect(effect) {
    this->effect = effect;
    this->position = position;
    sf::Sprite temp(texture);
    sf::Vector2u size = texture.getSize();
    float scale = float(radius) / size.x * 2;
    temp.setScale(scale, scale);
    temp.setPosition(position - sf::Vector2f(radius, radius));
    sprite = temp;
    usingTexture = true;
}

void PowerUp::setRadius(int radius) {
    this->radius = radius;
}

void PowerUp::setPosition(sf::Vector2f pos) {
    position = pos;
}

void PowerUp::pick_up(Head *player) {
    effect.setTarget(player);
    player->addEffect(&effect);
}

int PowerUp::getRadius() const {
    return radius;
}

bool PowerUp::isPickedUp() const {
    return pickedUp;
}

void PowerUp::setPickedUp(bool pickedUp) {
    PowerUp::pickedUp = pickedUp;
}

const sf::Vector2f &PowerUp::getPosition() const {
    return position;
}

const sf::Drawable &PowerUp::getShape() const {
    if(usingTexture)
        return sprite;
    else
        return shape;
}
