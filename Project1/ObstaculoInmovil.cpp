#include "ObstaculoInmovil.h"

ObstaculoInmovil::ObstaculoInmovil(
    b2World* mundo,
    const b2Vec2& posicion,
    const b2Vec2& halfSize,
    uintptr_t userData
) {
    CrearRectangulo(
        mundo,
        b2_staticBody,
        posicion,
        halfSize,
        1.f,
        0.3f,
        0.f,
        userData,
        Color::Blue
    );
    SetTexture("Images/metal.png");
}
