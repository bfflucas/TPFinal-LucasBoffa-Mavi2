#pragma once
#include "Ragdoll.h"
#include "Canion.h"

class Zombie : public Ragdoll {
public:
    Zombie(sf::Vector2f posicion, b2World* mundo, Canion* canion);

    void Update();          // se llama cada frame
    bool EstaMuerto() const { return muerto; }
    void MarcarMuerto() { muerto = true; }
    //void AplicarEmpujeInicial(const b2Vec2& f);
    // lo llama el ContactListener cuando toca el piso
    void SetEnSuelo(bool v);

    void PrepararParaCaminar();
    void CaminarHaciaCanion();


private:
    Canion* canion = nullptr;
    bool muerto = false;
    bool enSuelo = false;
    float velocidad = 2.5f; // ajustable
    
};
