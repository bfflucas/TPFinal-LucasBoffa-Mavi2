#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


using namespace sf;

class Actor {
private:
	b2Body* bdy_actor;
	RectangleShape* fig_actor;

	b2AABB dimensiones;
	b2Vec2 posicion;

public:

	Actor(b2Body* cuerpo, RectangleShape* figura);
	void dibujar(RenderWindow& ventana);
	float rad2deg(float radianes);

};
