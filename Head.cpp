// Created by brych on 29.12.18.
//

#include "Head.h"
#include "Game.h"
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
        int x = lround(position.x + cos(a) * width);
        int y = lround(position.y + sin(a) * width);

        sf::Color localColor = image.getPixel(x, y);
        if(localColor != parent->getSettings().backgroundColor){
            result.push_back(localColor);
        }
    }
    return result;
}

sf::VertexArray Head::wide_head() {
    sf::VertexArray result(sf::LinesStrip, 2);
    result[0].position.x = cos(angle - M_PI/2) * width + position.x;
    result[0].position.y = sin(angle - M_PI/2) * width + position.y;
    result[1].position.x = cos(angle + M_PI/2) * width + position.x;
    result[1].position.y = sin(angle + M_PI/2) * width + position.y;

    result[0].color = color;
    result[1].color = color;

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
    if(!alive)
        return ;

    float delta_x = cos(angle) * speed;
    float delta_y = sin(angle) * speed;

    position.x += delta_x;
    position.y += delta_y;

    bool outOfBounds = position.x < 0 + width || position.y < 0 + width || position.x > parent->getSettings().width - width || position.y > parent->getSettings().height - width;
    if (outOfBounds) {
        alive = false;
        return;
    }

    sf::VertexArray currentHead = wide_head();
    lines.append(currentHead[0]);
    lines.append(currentHead[1]);

    if(!ghost) {
        for (auto enemy: enemies) {
            float dist = sqrtf(powf(position.x - enemy->position.x, 2) + powf(position.y - enemy->position.y, 2));
            if (dist < width + enemy->width)
                alive = false;
        }

        std::vector<sf::Color> collisions = intersects(image);
        std::vector <sf::Color> enemyColors = getEnemyColors();

        for(auto collision: collisions){
            if(std::find(enemyColors.begin(), enemyColors.end(), collision) != enemyColors.end())
                alive = false;
            if(collision == color)
                alive = false;
        }
    }
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

//    sf::Vector2f rectPosition = currentHead[1].position;
//    sf::Vector2f rectSize(currentHead[0].position - currentHead[1].position);
//    sf::FloatRect newRect(rectPosition, rectSize);

//    sf::FloatRect lastRect = hitboxes[hitboxes.size() - 1];
//    if(fabs(lastRect.top - newRect.top) > fabs(lastRect.height) ||
//       fabs(lastRect.left - newRect.left) > fabs(lastRect.width)) {



//        hitboxes.push_back(newRect);
//    }

//    sf::Color background(0, 0, 0);
//    sf::Color testColor = image.getPixel(int(position.x+0.5), int(position.y + 0.5));
//    bool colision = image.getPixel(int(position.x+0.5), int(position.y + 0.5)) != background;
//    bool outOfBounds = position.x < 0 || position.y < 0 || position.x > 400 || position.y > 400;
//    if(colision || outOfBounds){
//        alive = false;
//        std::cout << "Dead";
//    }
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


