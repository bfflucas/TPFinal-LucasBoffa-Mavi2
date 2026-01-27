#include "Interruptor.h"

Interruptor::Interruptor(b2World* mundo, const b2Vec2& posicion, const b2Vec2& halfSize) {
    world = mundo;

    // body estatico
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = posicion;
    body = world->CreateBody(&bd);

    // shape
    b2PolygonShape sh;
    sh.SetAsBox(halfSize.x, halfSize.y);

    // fixture sensor
    b2FixtureDef fd;
    fd.shape = &sh;
    fd.isSensor = true;
    fd.userData.pointer = 50; // 50 = interruptor
    fixture = body->CreateFixture(&fd);

    // grafico
    figura = new sf::RectangleShape();
    figura->setFillColor(sf::Color::Magenta);

    actor = new Actor(body, figura);
}

Interruptor::~Interruptor() {
    delete actor; actor = nullptr;
    delete figura; figura = nullptr;

    if (body && world) {
        world->DestroyBody(body);
        body = nullptr;
    }
}

void Interruptor::Dibujar(sf::RenderWindow& wnd) {
    if (actor) actor->dibujar(wnd);
}
