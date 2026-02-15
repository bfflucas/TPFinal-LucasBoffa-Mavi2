#include "Obstaculo.h"

Obstaculo::~Obstaculo() {
    delete actor;
    delete figura;

    if (body && world) {
        world->DestroyBody(body);
        body = nullptr;
    }

}

void Obstaculo::Dibujar(RenderWindow& window) {
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
    const Color& color
) {

    world = mundo; // guardo el mundo para destruir el body despues

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

    figura = new RectangleShape();
    figura->setFillColor(color);

    actor = new Actor(body, figura);
}

bool Obstaculo::SetTexture(const string& path, float ppu, bool repetir) {
    if (!figura) return false;

    static std::map<string, Texture> cache;

    // Si no existe, la cargamos
    if (cache.find(path) == cache.end()) {
        Texture tex;
        if (!tex.loadFromFile(path))
            return false;

        tex.setRepeated(repetir);
        cache[path] = tex;
    }

    Texture& tex = cache[path];

    figura->setFillColor(Color::White);
    figura->setTexture(&tex);

    if (repetir) {
        Vector2f sz = figura->getSize();
        figura->setTextureRect(sf::IntRect(
            0, 0,
            (int)(sz.x * ppu),
            (int)(sz.y * ppu)
        ));
    }
    else {
        // usa la imagen completa (sin repetir)
        Vector2u ts = tex.getSize();
        figura->setTextureRect(IntRect(0, 0, (int)ts.x, (int)ts.y));
    }

    return true;
}

