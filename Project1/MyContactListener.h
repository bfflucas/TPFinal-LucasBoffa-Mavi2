#pragma once
#include "Includes.h"
#include "Ragdoll.h"
#include "Bola.h"
#include <Box2D/Box2D.h>

// Forward declaration para no romper includes
class Ragdoll;


using namespace sf;

class MyContactListener : public b2ContactListener {

public:
	void BeginContact(b2Contact* contact) override;
	b2Body* cuerpo_tocado = nullptr;

	Ragdoll* ragdoll_a_borrar = nullptr;
	Bola* bola_a_borrar = nullptr;

	bool nivel_superado = false;

	bool penalizar_tiempo = false;
};
