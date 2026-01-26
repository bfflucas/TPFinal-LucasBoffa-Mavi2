#pragma once
#include "Obstaculo.h"

class ObstaculoMovil : public Obstaculo {
public:
    ObstaculoMovil(
        b2World* mundo,
        const b2Vec2& posicionInicial,
        const b2Vec2& halfSize,
        float limiteMin,
        float limiteMax,
        float velocidad,
        bool movimientoHorizontal = true,
        uintptr_t userData = 3
    );

    void Update();

private:
    float min;
    float max;
    float vel;
    bool horizontal;
};
