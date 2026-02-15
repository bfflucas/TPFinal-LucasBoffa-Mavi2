#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

using namespace sf;

class Interruptor {
public:
    Interruptor(b2World* mundo, const b2Vec2& posicion, const b2Vec2& halfSize);
    ~Interruptor();

    void Dibujar(sf::RenderWindow& wnd);

private:
    b2World* world = nullptr;
    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;

    sf::RectangleShape* figura = nullptr;
    Actor* actor = nullptr;
};
