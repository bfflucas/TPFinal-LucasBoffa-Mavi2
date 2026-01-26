#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Trituradora {
public:
    Trituradora(
        b2World* mundo,
        const b2Vec2& posicion,
        const b2Vec2& halfSize,
        uintptr_t userData = 99,
        bool visible = true
    );

    ~Trituradora();

    void Dibujar(sf::RenderWindow& wnd);

    b2Body* GetBody() const { return body; }
    uintptr_t GetUserData() const { return tag; }

private:
    b2World* world = nullptr;

    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;

    sf::RectangleShape* figura = nullptr;
    Actor* actor = nullptr;

    uintptr_t tag = 99;
    bool drawVisible = true;
};
