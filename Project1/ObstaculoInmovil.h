#pragma once
#include "Obstaculo.h"

class ObstaculoInmovil : public Obstaculo {
public:
    ObstaculoInmovil(
        b2World* mundo,
        const b2Vec2& posicion,
        const b2Vec2& halfSize,
        uintptr_t userData = 3
    );
};
