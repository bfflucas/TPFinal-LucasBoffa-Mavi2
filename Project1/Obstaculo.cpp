#include "Obstaculo.h"

Obstaculo::~Obstaculo() {
    delete actor;
    delete figura;
}

void Obstaculo::Dibujar(sf::RenderWindow& window) {
    if (actor)
        actor->dibujar(window);
}

void Obstaculo::CrearRectangulo(
    b2World* mundo,
    b2BodyType tipo,
    const b2Vec2& posicion,
    const b2Vec2& halfSize,
    float densidad,
    float friccion,
    float restitucion,
    uintptr_t userData,
    const sf::Color& color
) {
    b2BodyDef bodyDef;
    bodyDef.type = tipo;
    bodyDef.position = posicion;

    body = mundo->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(halfSize.x, halfSize.y);

    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.density = densidad;
    fixDef.friction = friccion;
    fixDef.restitution = restitucion;
    fixDef.userData.pointer = userData;

    fixture = body->CreateFixture(&fixDef);

    figura = new sf::RectangleShape();
    figura->setFillColor(color);

    actor = new Actor(body, figura);
}
