#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Pendulo {
public:
    // anchorPos: donde esta colgado (cerca del techo)
    // largo: largo del "cuerpo" colgante (en unidades Box2D)
    // ancho: ancho del cuerpo colgante
    // densidad: que tan pesado es (mas densidad = mas masa)
    Pendulo(b2World* mundo, const b2Vec2& anchorPos, float largo = 8.0f, float ancho = 0.6f, float densidad = 6.0f);
    ~Pendulo();

    void IniciarMovimiento(float impulsoX = 40.0f);

    void Dibujar(sf::RenderWindow& wnd);

private:
    b2World* world = nullptr;

    b2Body* anchor = nullptr;           // soporte fijo
    b2Body* cuerpo = nullptr;           // cuerpo colgante (largo y pesado)
    b2RevoluteJoint* joint = nullptr;   // bisagra

    sf::RectangleShape* figAnchor = nullptr;
    sf::RectangleShape* figCuerpo = nullptr;

    Actor* actAnchor = nullptr;
    Actor* actCuerpo = nullptr;
};
