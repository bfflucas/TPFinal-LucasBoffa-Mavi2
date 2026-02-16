#include "Trituradora.h"

Trituradora::Trituradora(
    b2World* mundo,
    const b2Vec2& posicion,
    const b2Vec2& halfSize,
    bool visible,
    float limiteMinX,
    float limiteMaxX,
    float velocidad
) {

    static sf::Texture texSierra;
    static bool cargada = false;

    if (!cargada) {
        texSierra.loadFromFile("Images/trituradora.png");
        cargada = true;
    }

    world = mundo;

    minX = limiteMinX;
    maxX = limiteMaxX;
    vel = velocidad;
    dir = 1.f;


    // Body 
    b2BodyDef bd;
    bd.type = b2_kinematicBody;
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

    // Grafico
    figura = new RectangleShape(
        Vector2f(halfSize.x * 2.f, halfSize.y * 2.f)
    );
    figura->setOrigin(
        halfSize.x * 2.f / 2.f,
        halfSize.y * 2.f / 2.f
    );
    figura->setFillColor(Color::White);
    figura->setTexture(&texSierra);

    actor = new Actor(body, figura);

    // arrancar moviendose
    body->SetLinearVelocity(b2Vec2(vel * dir, 0.f));
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

void Trituradora::Actualizar() {
    if (!body) return;

    float x = body->GetPosition().x;

    // si llega a un limite, invierte direccion
    if (x >= maxX) {
        dir = -1.f;
        body->SetLinearVelocity(b2Vec2(vel * dir, 0.f));
    }
    else if (x <= minX) {
        dir = 1.f;
        body->SetLinearVelocity(b2Vec2(vel * dir, 0.f));
    }
}

void Trituradora::Dibujar(RenderWindow& wnd) {
    if (actor) actor->dibujar(wnd);
}
