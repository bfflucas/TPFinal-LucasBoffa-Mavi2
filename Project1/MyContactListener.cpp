#include "MyContactListener.h"



void MyContactListener::BeginContact(b2Contact* contact) {

	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	uintptr_t a = fA->GetUserData().pointer;
	uintptr_t b = fB->GetUserData().pointer;


	//====================== trituradora (99) vs ragdoll(1) =========================
	if ((a == 99 && b == 1) || (a == 1 && b == 99)) {

		// El fixture que pertenece al ragdoll es el que tiene userData=1
		b2Body* ragBody = (a == 1) ? fA->GetBody() : fB->GetBody();

		// Cada body del ragdoll debe tener guardado el puntero a su instancia:
		// bdy_rag[i]->GetUserData().pointer = (uintptr_t)this;
		Ragdoll* rag = reinterpret_cast<Ragdoll*>(ragBody->GetUserData().pointer);

		if (rag) {
			ragdoll_a_borrar = rag;
			penalizar_tiempo = true;
		}

		return; // no seguimos evaluando este contacto
	}

	// ==================INTERRUPTOR (50) vs RAGDOLL (1)====================================
	if ((a == 50 && b == 1) || (a == 1 && b == 50)) {
		nivel_superado = true;
		return;
	}


	// Verificamos si uno de los dos fixtures es un obstaculo
	if (a == 1 && b != 1) {
		cuerpo_tocado = fB->GetBody();
	}
	else if (b == 1 && a != 1) {
		cuerpo_tocado = fA->GetBody();
	}
	
   //================== BOLA (22) toca CAÑÓN (10)====================================
  
	if ((a == 22 && b == 10) || (a == 10 && b == 22)) {

		b2Body* bolaBody = (a == 22) ? fA->GetBody() : fB->GetBody();
		bola_a_borrar = reinterpret_cast<Bola*>(
			bolaBody->GetUserData().pointer
			);

		penalizar_tiempo = true;
		return;
	}

	//==================== BOLA (22) toca RAGDOLL (1)====================================

	if ((a == 22 && b == 1) || (a == 1 && b == 22)) {

		b2Body* bolaBody = (a == 22) ? fA->GetBody() : fB->GetBody();
		bola_a_borrar = reinterpret_cast<Bola*>(
			bolaBody->GetUserData().pointer
			);
		// El body del ragdoll (el fixture con userData=1)
		b2Body* ragBody = (a == 1) ? fA->GetBody() : fB->GetBody();
		Ragdoll* rag = reinterpret_cast<Ragdoll*>(ragBody->GetUserData().pointer);

		if (rag) {
			ragdoll_a_borrar = rag;   // reutilizamos el mismo puntero
		}
		return;
	}

	// BOLA (22) toca PISO (30) => ya puede caminar
	if ((a == 22 && b == 30) || (a == 30 && b == 22)) {

		b2Body* bodyBola = (a == 22) ? fA->GetBody() : fB->GetBody();

		Bola* z = reinterpret_cast<Bola*>(bodyBola->GetUserData().pointer);
		if (z) {
			z->SetEnSuelo(true);
		}
		return;
	}
}

//==================================PARA IGNORAR CONTACTOS============================

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	auto* a = contact->GetFixtureA();
	auto* b = contact->GetFixtureB();

	uintptr_t ta = a->GetUserData().pointer;
	uintptr_t tb = b->GetUserData().pointer;

	// 22 = bola, 40 = obstaculo movil 
	bool bola_mov =
		(ta == 22 && tb == 40) ||
		(ta == 40 && tb == 22);

	if (bola_mov) {
		contact->SetEnabled(false);
	}
}

