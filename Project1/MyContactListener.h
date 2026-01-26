#pragma once
#include "Includes.h"


using namespace sf;

class MyContactListener : public b2ContactListener {

public:
	void BeginContact(b2Contact* contact) override;
	b2Body* cuerpo_tocado = nullptr;
	//bool touched = false;
};
