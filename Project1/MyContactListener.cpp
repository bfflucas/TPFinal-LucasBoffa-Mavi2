#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact) {

	b2FixtureUserData B2B = contact->GetFixtureB()->GetUserData();
	b2FixtureUserData B2A = contact->GetFixtureA()->GetUserData();

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();


	// Verificamos si uno de los dos fixtures es un obstáculo fijo
	if (B2A.pointer == 2 ) {
		cuerpo_tocado = fixtureA->GetBody();
	}
	else if (B2B.pointer == 2 ) {
		cuerpo_tocado = fixtureB->GetBody();
	}
	
}

