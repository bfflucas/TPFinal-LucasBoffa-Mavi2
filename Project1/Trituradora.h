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
        bool visible,
        float limiteMinX,
        float limiteMaxX,
        float velocidad
    );

    ~Trituradora();
    void Actualizar();
    void Dibujar(RenderWindow& wnd);

    b2Body* GetBody() const { return body; }
    uintptr_t GetUserData() const { return tag; }

private:
    b2World* world = nullptr;

    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;

    RectangleShape* figura = nullptr;
    Actor* actor = nullptr;

    uintptr_t tag = 99; // para el contact listener

    // movimiento tipo "fuego"
    float minX = 0.f;
    float maxX = 0.f;
    float vel = 0.f;      // unidades Box2D por segundo aprox
    float dir = 1.f;      // 1 o -1
};
