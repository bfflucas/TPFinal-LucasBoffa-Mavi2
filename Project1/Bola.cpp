#include "Bola.h"

Bola::Bola(b2World* w, const b2Vec2& pos, float radio, Canion* c)
    : world(w), canion(c)
{
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = pos;
    body = world->CreateBody(&bd);

    b2CircleShape sh;
    sh.m_radius = radio;

    b2FixtureDef fd;
    fd.shape = &sh;
    fd.density = 1.f;
    fd.friction = 0.8f;      // mas friccion = rueda menos loca
    fd.restitution = 0.2f;
    fd.userData.pointer = 22; // tag bola
    body->CreateFixture(&fd);

    // para poder "identificar" esta bola desde contactos si queres
    body->GetUserData().pointer = (uintptr_t)this;

    figura = new sf::CircleShape();
    figura->setRadius(radio);
    figura->setOrigin(radio, radio);
    figura->setFillColor(sf::Color(200, 200, 0));
}

Bola::~Bola() {
    delete figura; figura = nullptr;

    if (body && world) {
        world->DestroyBody(body);
        body = nullptr;
    }
}

void Bola::Dibujar(sf::RenderWindow& wnd) {
    if (!body || !figura) return;

    b2Vec2 p = body->GetPosition();
    figura->setPosition(p.x, p.y);
    wnd.draw(*figura);
}

void Bola::SetEnSuelo(bool v) {
    if (enSuelo == v) return;
    enSuelo = v;
}

void Bola::Update() {
    if (muerto || !canion || !body) return;
    if (!enSuelo) return;

    HaciaCanion();
}

void Bola::HaciaCanion() {
    b2Vec2 posCanion = canion->GetBody()->GetPosition();
    b2Vec2 posBola = body->GetPosition();

    float dx = posCanion.x - posBola.x;
    float dir = (dx > 0.f) ? 1.f : -1.f;

    // fuerza horizontal para que ruede hacia el canion
    body->ApplyForceToCenter(b2Vec2(dir * velocidad, 0.f), true);
}
