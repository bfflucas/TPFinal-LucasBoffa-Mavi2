#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Canion.h"

class Bola {
public:
    Bola(b2World* world, const b2Vec2& pos, float radio, Canion* canion);
    ~Bola();

    void Dibujar(sf::RenderWindow& wnd);
    b2Body* GetBody() { return body; }
    void Update();
    void SetEnSuelo(bool v);
    void HaciaCanion();

private:
    b2World* world = nullptr;
    b2Body* body = nullptr;

    sf::CircleShape* figura = nullptr;

    Canion* canion = nullptr;
    bool muerto = false;
    bool enSuelo = false;
    float velocidad = 5.5f; // ajustable

};
