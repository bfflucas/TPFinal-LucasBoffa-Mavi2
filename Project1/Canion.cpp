#include "Canion.h"
#include <cmath> // atan2f, cos, sin

static sf::Texture texCanion;

Canion::Canion(b2World* mundo, const b2Vec2& posicion) {
    world = mundo;

    // Body static
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = posicion;
    body = world->CreateBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(1.2f, 0.9f);

    // Fixture
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.restitution = 0.3f;
    fd.friction = 0.3f;

    // TAG para el ContactListener
    fd.userData.pointer = 10;

    fixture = body->CreateFixture(&fd);

    // Grafico

    // ===== TEXTURA =====
    static bool cargada = false;
    if (!cargada) {
        texCanion.loadFromFile("Images/canion.png");
        cargada = true;
    }

    figura = new sf::RectangleShape();
    figura->setFillColor(sf::Color::White);
    figura->setTexture(&texCanion);

    // que use toda la imagen (sin repetir)
    sf::Vector2u ts = texCanion.getSize();
    figura->setTextureRect(sf::IntRect(0, 0, (int)ts.x, (int)ts.y));

    actor = new Actor(body, figura);
}

Canion::~Canion() {
    delete actor; actor = nullptr;
    delete figura; figura = nullptr;

    if (body && world) {
        world->DestroyBody(body);
        body = nullptr;
    }
}

void Canion::Dibujar(sf::RenderWindow& wnd) {
    if (actor) actor->dibujar(wnd);
}

void Canion::SetAngle(float radianes) {
    if (!body) return;

    // limites: -90 a 0 grados
    float minA = deg2rad(-90.f);
    float maxA = deg2rad(0.f);

    if (radianes < minA) radianes = minA;
    if (radianes > maxA) radianes = maxA;

    body->SetTransform(body->GetPosition(), radianes);
}


void Canion::UpdateAimMouse(sf::RenderWindow& wnd) {
    if (!body) return;

    sf::Vector2i posicion_m = sf::Mouse::getPosition(wnd);
    sf::Vector2f mouseWorld = wnd.mapPixelToCoords(posicion_m);

    float cx = body->GetPosition().x;
    float cy = body->GetPosition().y;

    float angulo_objetivo = atan2f(mouseWorld.y - cy, mouseWorld.x - cx);

    // clamp -90 a 0
    float limite_min = deg2rad(-90.f);
    float limite_max = deg2rad(0.f);

    if (angulo_objetivo < limite_min) angulo_objetivo = limite_min;
    if (angulo_objetivo > limite_max) angulo_objetivo = limite_max;

    body->SetTransform(body->GetPosition(), angulo_objetivo);
}
