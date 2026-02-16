#include "Interruptor.h"

static Texture texture;

Interruptor::Interruptor(b2World* mundo, const b2Vec2& posicion, const b2Vec2& halfSize) {
    

    static bool cargada = false;

    if (!cargada) {
        texture.loadFromFile("Images/exit.png");
        cargada = true;
    }

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
    fd.userData.pointer = 50; // para el contact listener
    fixture = body->CreateFixture(&fd);

    // grafico
    figura = new sf::RectangleShape();
    figura->setFillColor(Color::White);
    figura->setTexture(&texture);

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

void Interruptor::Dibujar(RenderWindow& wnd) {
    if (actor) actor->dibujar(wnd);
}
