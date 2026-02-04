#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Actor.h"

class Obstaculo {
public:
    virtual ~Obstaculo();

    void Dibujar(sf::RenderWindow& window);
    b2Body* GetBody() const { return body; }

    // asignar sprite al rectangulo del obstaculo
    bool SetTexture(const std::string& path, float ppu = 120.f, bool repetir = true);


protected:
    Obstaculo() = default;

    void CrearRectangulo(
        b2World* mundo,
        b2BodyType tipo,
        const b2Vec2& posicion,
        const b2Vec2& halfSize,
        float densidad,
        float friccion,
        float restitucion,
        uintptr_t userData,
        const sf::Color& color
    );

protected:
    b2World* world = nullptr;          //para DestroyBody
    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;

    sf::RectangleShape* figura = nullptr;
    Actor* actor = nullptr;

    sf::Texture* textura = nullptr;    // debe vivir en el objeto

};
