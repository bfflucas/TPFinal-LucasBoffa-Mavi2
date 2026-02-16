#include "ObstaculoMovil.h"

ObstaculoMovil::ObstaculoMovil(
    b2World* mundo,
    const b2Vec2& posicionInicial,
    const b2Vec2& halfSize,
    float limiteMin,
    float limiteMax,
    float velocidad,
    bool movimientoHorizontal,
    uintptr_t userData
) {
    min = limiteMin;
    max = limiteMax;
    vel = velocidad;
    horizontal = movimientoHorizontal;

    CrearRectangulo(
        mundo,
        b2_kinematicBody,     // CLAVE: es kinematic
        posicionInicial,
        halfSize,
        1.f,
        1.f,
        0.f,
        userData,
        sf::Color::Yellow
    );
    SetTexture("Images/nube.png", 120.f, false);
}

void ObstaculoMovil::Update() {
    if (!body) return;

    b2Vec2 pos = body->GetPosition();

    if (horizontal) {
        if (pos.x >= max) vel = -std::abs(vel);
        if (pos.x <= min) vel = std::abs(vel);

        body->SetLinearVelocity(b2Vec2(vel, 0.f));
    }
    else {
        if (pos.y >= max) vel = -std::abs(vel);
        if (pos.y <= min) vel = std::abs(vel);

        body->SetLinearVelocity(b2Vec2(0.f, vel));
    }
}
