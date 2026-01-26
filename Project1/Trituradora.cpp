#include "Trituradora.h"

Trituradora::Trituradora(
    b2World* mundo,
    const b2Vec2& posicion,
    const b2Vec2& halfSize,
    uintptr_t userData,
    bool visible
) {
    world = mundo;
    tag = userData;
    drawVisible = visible;

    // Body estatico
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = posicion;
    body = world->CreateBody(&bd);

    // Shape
    b2PolygonShape sh;
    sh.SetAsBox(halfSize.x, halfSize.y);

    // Fixture SENSOR
    b2FixtureDef fd;
    fd.shape = &sh;
    fd.isSensor = true;
    fd.userData.pointer = tag;
    fixture = body->CreateFixture(&fd);

    // Grafico (opcional)
    figura = new sf::RectangleShape();
    if (drawVisible) {
        figura->setFillColor(sf::Color(255, 0, 0, 120)); // rojo transparente
    }
    else {
        figura->setFillColor(sf::Color(0, 0, 0, 0));     // invisible
    }

    actor = new Actor(body, figura);
}

Trituradora::~Trituradora() {
    // destruir en orden seguro
    delete actor; actor = nullptr;
    delete figura; figura = nullptr;

    if (body && world) {
        world->DestroyBody(body);
        body = nullptr;
    }
}

void Trituradora::Dibujar(sf::RenderWindow& wnd) {
    if (!drawVisible) return;
    if (actor) actor->dibujar(wnd);
}
