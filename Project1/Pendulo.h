#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Pendulo {
public:
    // anchorPos: donde esta colgado (cerca del techo)
    // largo: largo del "cuerpo" colgante (en unidades Box2D)
    // ancho: ancho del cuerpo colgante

    Pendulo(b2World* mundo, const b2Vec2& anchorPos,
        float largo = 8.0f, float ancho = 0.6f, float densidad = 6.0f);
    ~Pendulo();

    void IniciarMovimiento(float impulsoX = 40.0f);
    void Dibujar(RenderWindow& wnd);

private:
    b2World* world = nullptr;

    // fisica
    b2Body* anchor = nullptr;           // soporte fijo
    b2Body* cuerpo = nullptr;           // barra/cadena (cuerpo largo)
    b2Body* punta = nullptr;           // punta cuadrada

    b2RevoluteJoint* joint = nullptr;   // bisagra anchor - cuerpo
    b2WeldJoint* jointPunta = nullptr;  // soldadura cuerpo - punta

    // graficos
    RectangleShape* figAnchor = nullptr;
    RectangleShape* figCuerpo = nullptr;
    RectangleShape* figPunta = nullptr;

    Actor* actAnchor = nullptr;
    Actor* actCuerpo = nullptr;
    Actor* actPunta = nullptr;
};
