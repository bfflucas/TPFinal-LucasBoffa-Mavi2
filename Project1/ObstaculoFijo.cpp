#include "ObstaculoFijo.h"

ObstaculoFijo::ObstaculoFijo(
    b2World* mundo,
    const b2Vec2& posicion,
    const b2Vec2& halfSize,
    uintptr_t userData
) {
    CrearRectangulo(
        mundo,
        b2_kinematicBody,
        posicion,
        halfSize,
        1.f,
        0.3f,
        0.f,
        userData,
        sf::Color::Yellow
    );
}
