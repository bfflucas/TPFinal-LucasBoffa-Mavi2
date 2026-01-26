#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Obstaculo {
public:
    virtual ~Obstaculo();

    void Dibujar(sf::RenderWindow& window);
    b2Body* GetBody() const { return body; }

protected:
    Obstaculo() = default;

    void CrearRectangulo(
        b2World* mundo,
        b2BodyType tipo,
        const b2Vec2& posicion,
        const b2Vec2& halfSize,
        float densidad,
        float friccion,
        float restitucion,
        uintptr_t userData,
        const sf::Color& color
    );

protected:
    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;

    sf::RectangleShape* figura = nullptr;
    Actor* actor = nullptr;
};
