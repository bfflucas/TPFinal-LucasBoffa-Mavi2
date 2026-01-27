#include "MyContactListener.h"
#include "Ragdoll.h"


void MyContactListener::BeginContact(b2Contact* contact) {

	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	uintptr_t a = fA->GetUserData().pointer;
	uintptr_t b = fB->GetUserData().pointer;


	// 99 = trituradora, 1 = ragdoll
	if ((a == 99 && b == 1) || (a == 1 && b == 99)) {

		// El fixture que pertenece al ragdoll es el que tiene userData=1
		b2Body* ragBody = (a == 1) ? fA->GetBody() : fB->GetBody();

		// Cada body del ragdoll debe tener guardado el puntero a su instancia:
		// bdy_rag[i]->GetUserData().pointer = (uintptr_t)this;
		Ragdoll* rag = reinterpret_cast<Ragdoll*>(ragBody->GetUserData().pointer);

		// Guardar para borrar luego (NO borrar aca)
		// Si preferis no pisar uno anterior, podes chequear si ya hay uno.
		if (rag) {
			ragdoll_a_borrar = rag;
		}

		return; // no seguimos evaluando este contacto
	}

	// INTERRUPTOR (50) vs RAGDOLL (1)
	if ((a == 50 && b == 1) || (a == 1 && b == 50)) {
		nivel_superado = true;
		return;
	}


	// Verificamos si uno de los dos fixtures es un obstáculo
	if (a == 1 && b != 1) {
		cuerpo_tocado = fB->GetBody();
	}
	else if (b == 1 && a != 1) {
		cuerpo_tocado = fA->GetBody();
	}
	
}

