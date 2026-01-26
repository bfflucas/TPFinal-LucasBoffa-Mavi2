#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Pendulo {
public:
    Pendulo(b2World* mundo, const b2Vec2& anchorPos);
    ~Pendulo();

    void Dibujar(sf::RenderWindow& wnd);

    b2Body* GetBobBody() const { return bob; } // cuerpo que cuelga (para colisiones)
private:
    b2World* world = nullptr;

    b2Body* anchor = nullptr;
    b2Body* bob = nullptr;
    b2RevoluteJoint* joint = nullptr;

    sf::RectangleShape* figAnchor = nullptr;
    sf::RectangleShape* figBob = nullptr;

    Actor* actAnchor = nullptr;
    Actor* actBob = nullptr;
};
