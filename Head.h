//
// Created by brych on 29.12.18.
//

#ifndef HELLOSFML_HEAD_H
#define HELLOSFML_HEAD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Game;
class Effect;

class Head{
private:
    // drawing stuff
    sf::Vector2f position;
    sf::VertexArray lines;
    sf::Color color= sf::Color(0, 255, 0);

    // current properties
    int width;
    float speed;
private:
    double angle;
    bool ghost = false; // if true, doesn't leave trail and is immune to collisions
    int ghostTimer = 60;  // how many frames does ghost last
    bool alive = true;

    std::vector <Head *> enemies;  // pointers to all enemies. Used for collision detection
    std::vector <Effect *> effects;
    Game* parent;

    sf::VertexArray wide_head();  // returns array representing the line at the and of 'snake'
    std::vector <sf::Color> intersects(sf::Image &image);  // returbs an array of all pixel colors

public:
    bool isAlive() const;

    Head(float startX, float startY, int startWidth, float startSpeed, double angle);

    sf::Vector2f getPosition();
    sf::VertexArray getShape();
    sf::CircleShape getHeadShape();
    std::vector <Head *> getEnemies();
    std::vector <sf::Color> getEnemyColors();

    void turn(double angle);

    void update(sf::Image &image);
    void addEnemy(Head * enemy);
    void addEffect(Effect  * effect);
    const sf::Color &getColor() const;

    void setColor(const sf::Color &color);
    float getSpeed() const;
    void setSpeed(float speed);
    bool isGhost() const;

    void setGhost(bool ghost);
    void setParent(Game * game);
    Game * getParent();

};


#endif //HELLOSFML_HEAD_H
