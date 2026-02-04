#include "Zombie.h"

Zombie::Zombie(sf::Vector2f posicion, b2World* mundo, Canion* c)
    : Ragdoll(posicion, mundo), canion(c)
{
    // Opcional: color distinto para distinguirlos
    for (int i = 0; i < 6; i++) {
        fig_rag[i]->setFillColor(sf::Color(0, 180, 0)); // verde zombie
    }

    SetUserData(22);
    // IMPORTANTE: cualquier body del ragdoll que colisione debe devolver "this"
    for (int i = 0; i < 6; i++) {
        bdy_rag[i]->GetUserData().pointer = (uintptr_t)this;
    }


    //arranca cayendo
    enSuelo = false;
}

void Zombie::SetEnSuelo(bool v) {
    // evita que lo setees 200 veces
    if (enSuelo == v) return;
    enSuelo = v;

    if (enSuelo) {
        PrepararParaCaminar();
    }
}

void Zombie::PrepararParaCaminar() {
    // “Enderezar” un poco y frenar el ragdoll para que parezca que se para

    for (int i = 0; i < 6; i++) {
        bdy_rag[i]->SetAngularVelocity(0.f);
        bdy_rag[i]->SetLinearDamping(2.5f);
        bdy_rag[i]->SetAngularDamping(6.0f);

        // si lo dejas flopper, no camina nunca.
        bdy_rag[i]->SetFixedRotation(true);
    }
}

void Zombie::Update() {
    if (muerto || !canion) return;

    b2Vec2 posCanion = canion->GetBody()->GetPosition();

    if (!enSuelo) return;

    CaminarHaciaCanion();

}

void Zombie::CaminarHaciaCanion() {
    if (enSuelo) {
        b2Vec2 posCanion = canion->GetBody()->GetPosition();

        // Usa el pecho como referencia (indice 1 en tu ragdoll)
        b2Vec2 posTorso = bdy_rag[1]->GetPosition();

        float dx = posCanion.x - posTorso.x;

        // direccion horizontal solamente
        float dir = (dx > 0.f) ? 1.f : -1.f;

        // fuerza horizontal (sin tocar Y)
        b2Vec2 f(dir * velocidad, 0.f);

        // aplica en torso y piernas para que “avance”
        bdy_rag[1]->ApplyForceToCenter(f, true);
        bdy_rag[4]->ApplyForceToCenter(f, true);
        bdy_rag[5]->ApplyForceToCenter(f, true);
    }

    
}

