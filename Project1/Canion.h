#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Canion {
public:
    Canion(b2World* mundo, const b2Vec2& posicion);
    ~Canion();

    void Dibujar(sf::RenderWindow& wnd);

    // Apunta hacia el mouse usando tu view/camara actual
    void UpdateAimMouse(sf::RenderWindow& wnd);

    // Por si queres moverlo por teclado
    void Rotar(float radianes);

    b2Body* GetBody() const { return body; }
    float GetAngle() const { return body ? body->GetAngle() : 0.f; }
    void SetAngle(float radianes);
private:
    float deg2rad(float grados) { return grados * 3.1415926f / 180.f; }

private:
    b2World* world = nullptr;
    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;

    sf::RectangleShape* figura = nullptr;
    Actor* actor = nullptr;
};
