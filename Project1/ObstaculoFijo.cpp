#include "ObstaculoFijo.h"

static Texture texBloque;

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
        Color::Yellow
    );

    // Cargar textura UNA sola vez
    static bool cargada = false;
    if (!cargada) {
        texBloque.loadFromFile("../Images/ladrillo.png");
        texBloque.setRepeated(true); 
        cargada = true;
    }

    // Asignar textura
    SetTexture("../Images/ladrillo.png");
}
