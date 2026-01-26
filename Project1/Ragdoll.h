#pragma once
#include "Actor.h"


class Ragdoll {

private:
	RectangleShape* fig_rag[6];
	Actor* act_rag[6];
	b2World* mundo;

	//Resortes
	b2DistanceJoint* jnt_rag[5];
	b2DistanceJointDef jntdef_rag[5];

	//Ragdoll
	b2Body* bdy_rag[6];
	b2BodyDef bdydef_rag[6];
	b2Fixture* fix_rag[6];
	b2FixtureDef fixdef_rag[6];

public:
	Ragdoll(Vector2f posicion, b2World* mundo1);
	~Ragdoll();
	void Dibujar(RenderWindow& wnd);
	void aplicar_fuerza(Vector2f posicion_m);
};