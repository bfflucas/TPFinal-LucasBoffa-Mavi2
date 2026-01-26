#pragma once
#include "Obstaculo.h"

class ObstaculoFijo : public Obstaculo {
public:
    ObstaculoFijo(
        b2World* mundo,
        const b2Vec2& posicion,
        const b2Vec2& halfSize,
        uintptr_t userData = 2
    );
};
