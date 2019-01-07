// Created by brych on 29.12.18.
//

#include "Head.h"
#include "Game.h"
#include "Effect.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#define SWEEP_RESOLUTION 100

Head::Head(float startX, float startY,  int startWidth, float startSpeed, double angle) {
    // Constructor.
    position.x = startX;
    position.y = startY;
    this->angle = angle;
    speed = startSpeed;
    width = startWidth;

    lines.setPrimitiveType(sf::TrianglesStrip);
    sf::VertexArray currentHead = wide_head();
    // init the first line
    lines.append(currentHead[0]);
    lines.append(currentHead[1]);
}

sf::Vector2f Head::getPosition() {
    return position;
}

sf::VertexArray Head::getShape() {
    return lines;
}

sf::CircleShape Head::getHeadShape() {
    // returns CircleShape representing the head
    sf::CircleShape result;
    result.setFillColor(sf::Color::Yellow);
    result.setPosition(position.x - width, position.y - width);
    result.setRadius(width);

    return result;
}

std::vector <Head *> Head::getEnemies() {
    return enemies;
}

std::vector <sf::Color> Head::getEnemyColors() {
    std::vector <sf::Color> result;
    for(auto enemy: enemies){
        result.push_back(enemy->color);
    }
    return result;
    //TODO have it return  a vector of pointers to Head::color
}

bool Head::isAlive() const {
    return alive;
}

void Head::addEnemy(Head * enemy) {
    enemies.push_back(enemy);
}

void Head::setParent(Game *game) {
    parent = game;
}

Game * Head::getParent() {
    return parent;
}

std::vector<sf::Color> Head::intersects(sf::Image &image) {
    std::vector<sf::Color> result;

    for(double a=angle - M_PI/2.2; a < angle + M_PI/2.2; a += M_PI/SWEEP_RESOLUTION){
        // x and y lie on semicircle in front of head
        int x = lround(position.x + cos(a) * width);
        int y = lround(position.y + sin(a) * width);

        sf::Color localColor = image.getPixel(x, y);
        if(localColor != parent->getSettings().backgroundColor){
            result.push_back(localColor);
            // because of antialiasing this will contain many false positives
            // TODO dosomething about it
        }
    }
    return result;
}

sf::VertexArray Head::wide_head() {
    // returns two points at the and of 'snake' this could be simple vector, but... idk
    sf::VertexArray result(sf::LinesStrip, 2);
    result[0].position.x = cos(angle - M_PI/2) * width + position.x;
    result[0].position.y = sin(angle - M_PI/2) * width + position.y;
    result[1].position.x = cos(angle + M_PI/2) * width + position.x;
    result[1].position.y = sin(angle + M_PI/2) * width + position.y;

    result[0].color = color;
    result[1].color = color;

    // make it transparent in ghost
    if(ghost){
        result[0].color.a=0;
        result[1].color.a=0;
    }

    return result;
}

void Head::turn(double angle) {
    this->angle += angle;
}

void Head::update(sf::Image &image) {
    // don't bother if player is dead
    if(!alive)
        return ;

    // movement
    float delta_x = cos(angle) * speed;
    float delta_y = sin(angle) * speed;

    position.x += delta_x;
    position.y += delta_y;

    bool outOfBounds = position.x < 0 + width || position.y < 0 + width || position.x > parent->getSettings().width - width || position.y > parent->getSettings().height - width;
    if (outOfBounds) {
        alive = false;
        return;
    }

    // add movement to lines to be drawn
    sf::VertexArray currentHead = wide_head();
    lines.append(currentHead[0]);
    lines.append(currentHead[1]);

    //apply effects
    for(auto it=effects.begin(); it != effects.end(); ++it){
        if((*it)->update()) {
            // I can't do pointers
            // memory leaks are here
//            delete *it;
            effects.erase(it);
            --it;
        }
    }

    // manage collisions only if not in ghost
    if(!ghost) {
        for (auto enemy: enemies) {
            float dist = sqrtf(powf(position.x - enemy->position.x, 2) + powf(position.y - enemy->position.y, 2));
            // if distance is smaller than the sum of the radii, there is collision
            if (dist < width + enemy->width)
                alive = false;
        }

        std::vector<sf::Color> collisions = intersects(image);
        std::vector <sf::Color> enemyColors = getEnemyColors();

        for(auto collision: collisions){
            // if color of collision belongs to enemy or player, die
            if(std::find(enemyColors.begin(), enemyColors.end(), collision) != enemyColors.end())
                alive = false;
            if(collision == color)
                alive = false;
        }
    }
    // handle ghost
    if(ghostTimer == 0){
        if(ghost){
            setGhost(false);
            ghostTimer = parent->getSettings().ghostFrames * parent->getSettings().ghostProportion;
        }
        else{
            setGhost(true);
            ghostTimer = parent->getSettings().ghostFrames;
        }
    }

    ghostTimer--;
}

bool Head::isGhost() const {
    return ghost;
}

void Head::setGhost(bool ghost) {
    Head::ghost = ghost;
}

const sf::Color &Head::getColor() const {
    return color;
}

void Head::setColor(const sf::Color &color) {
    Head::color = color;
}

float Head::getSpeed() const {
    return speed;
}

void Head::setSpeed(float speed) {
    Head::speed = speed;
}

void Head::addEffect(Effect * effect) {
    effects.push_back(effect);
}

int Head::getWidth() const {
    return width;
}

void Head::setWidth(int width) {
    Head::width = width;
}


