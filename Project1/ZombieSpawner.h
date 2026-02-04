#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Actor.h"
#include "Canion.h"
#include "Bola.h"

class ZombieSpawner {
public:
    ZombieSpawner(b2World* mundo, const b2Vec2& posicion, Canion* c);
    ~ZombieSpawner();

    void Actualizar(float dt);
    void Dibujar(sf::RenderWindow& wnd);
    void BorrarBolas(Bola* b);

private:
    void SpawnBola();

    b2World* world = nullptr;
    Canion* canion = nullptr;

    b2Body* ancla = nullptr;          // punto fijo en el techo
    b2Body* body = nullptr;           // arana (spawner)
    b2DistanceJoint* cuerdaJoint = nullptr;

    // grafico spawner
    sf::RectangleShape* figura = nullptr;
    Actor* actor = nullptr;

    // grafico cuerda (rectangulo fino)
    sf::RectangleShape* fig_cuerda = nullptr;
    float grosorCuerda = 0.2f;
    float offsetInicioCuerda = 0.0f;  // si queres que no nazca EXACTO del punto

    // config cuerda y balanceo
    float largoCuerda = 6.f;         // hace mas largo aca
    float fuerzaBalanceo = 25.f;      // fuerza horizontal
    float periodoBalanceo = 1.0f;     // segundos (mas chico = mas rapido)
    float tBalanceo = 0.f;

    // bolas
    std::vector<Bola*> bolas;
    float timer = 0.f;
    float cooldown = 2.0f;
};
