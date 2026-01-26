#include "Ragdoll.h"

Ragdoll::Ragdoll(Vector2f posicion, b2World* mundo1) : mundo(mundo1) {


	//Cuerpo ragdoll
	posicion.y -= 0.8;
	//Posicionando objetos

	bdydef_rag[0].position = b2Vec2(posicion.x, posicion.y + 0.1f); //Cabeza
	bdydef_rag[1].position = b2Vec2(posicion.x, posicion.y + 0.65f); //Pecho
	bdydef_rag[2].position = b2Vec2(posicion.x + 0.32f, posicion.y + 0.5f); //BD
	bdydef_rag[3].position = b2Vec2(posicion.x - 0.32f, posicion.y + 0.5f); //BI
	bdydef_rag[4].position = b2Vec2(posicion.x + 0.09f, posicion.y + 1.5f); //PD
	bdydef_rag[5].position = b2Vec2(posicion.x - 0.09f, posicion.y + 1.5f); //PI


	for (int i = 0; i < 6; i++) {
		bdydef_rag[i].type = b2_dynamicBody;
		bdy_rag[i] = mundo->CreateBody(&bdydef_rag[i]);
	}

	b2PolygonShape shp_rag[6];

	//Dimensiones del cuerpo
	shp_rag[0].SetAsBox(0.1, 0.1);
	shp_rag[1].SetAsBox(0.2, 0.4);
	shp_rag[2].SetAsBox(0.07, 0.3);
	shp_rag[3].SetAsBox(0.07, 0.3);
	shp_rag[4].SetAsBox(0.07, 0.4);
	shp_rag[5].SetAsBox(0.07, 0.4);

	fixdef_rag[0].userData.pointer = 1;

	for (int i = 0; i < 6; i++) {

		fixdef_rag[i].shape = &shp_rag[i];
		fixdef_rag[i].density = 1.f;
		fixdef_rag[i].friction = 0.3f;
		fixdef_rag[i].restitution = 0.7f;
		fixdef_rag[i].userData.pointer = 1;
		fix_rag[i] = bdy_rag[i]->CreateFixture(&fixdef_rag[i]);

	}

	//resortes

	jntdef_rag[0].Initialize(bdy_rag[0], bdy_rag[1], b2Vec2(bdy_rag[0]->GetPosition().x, bdy_rag[0]->GetPosition().y + 0.08), b2Vec2(bdy_rag[1]->GetPosition().x, bdy_rag[1]->GetPosition().y - 0.38));
	jntdef_rag[1].Initialize(bdy_rag[1], bdy_rag[2], b2Vec2(bdy_rag[1]->GetPosition().x + 0.18, bdy_rag[1]->GetPosition().y - 0.38), b2Vec2(bdy_rag[2]->GetPosition().x - 0.05, bdy_rag[2]->GetPosition().y - 0.28));
	jntdef_rag[2].Initialize(bdy_rag[1], bdy_rag[3], b2Vec2(bdy_rag[1]->GetPosition().x - 0.18, bdy_rag[1]->GetPosition().y - 0.38), b2Vec2(bdy_rag[3]->GetPosition().x + 0.05, bdy_rag[3]->GetPosition().y - 0.28));
	jntdef_rag[3].Initialize(bdy_rag[1], bdy_rag[4], b2Vec2(bdy_rag[1]->GetPosition().x + 0.09, bdy_rag[1]->GetPosition().y + 0.38), b2Vec2(bdy_rag[4]->GetPosition().x, bdy_rag[4]->GetPosition().y - 0.38));
	jntdef_rag[4].Initialize(bdy_rag[1], bdy_rag[5], b2Vec2(bdy_rag[1]->GetPosition().x - 0.09, bdy_rag[1]->GetPosition().y + 0.38), b2Vec2(bdy_rag[5]->GetPosition().x, bdy_rag[5]->GetPosition().y - 0.38));

	for (int i = 0; i < 5; i++) {
		jntdef_rag[i].damping = 0.3f;
		jntdef_rag[i].length = 0.025f;
		jntdef_rag[i].collideConnected = true;
		//jntdef_rag[i].SetFrequencyHz = 4.f;  
		jnt_rag[i] = (b2DistanceJoint*)mundo->CreateJoint(&jntdef_rag[i]);
	}

	//iniciando imagenes

	for (int i = 0; i < 6; i++) {
		fig_rag[i] = new RectangleShape;

	}
	fig_rag[0]->setFillColor(Color::Red);
	fig_rag[1]->setFillColor(Color::Red);
	fig_rag[2]->setFillColor(Color::Yellow);
	fig_rag[3]->setFillColor(Color::Yellow);
	fig_rag[4]->setFillColor(Color::Yellow);
	fig_rag[5]->setFillColor(Color::Yellow);

	
	for (int i = 0; i < 6; i++) {
		act_rag[i] = new Actor(bdy_rag[i], fig_rag[i]);
	}



}


void Ragdoll::Dibujar(RenderWindow& wnd) {

	for (int i = 0; i < 6; i++) {
		act_rag[i]->dibujar(wnd);
	}
}

void Ragdoll::aplicar_fuerza(Vector2f posicion_m) {

	for (int i = 0; i < 6; i++) {
		//bdy_rag[i]->ApplyForceToCenter(b2Vec2(bdy_rag[i]->GetPosition().x * fuerza * cos(angulo), bdy_rag[i]->GetPosition().y * fuerza * sin(angulo)), false);

		bdy_rag[i]->ApplyForceToCenter(b2Vec2(posicion_m.x * 10, posicion_m.y * 10), false);
	}

}

Ragdoll::~Ragdoll() {
	// Eliminar juntas
	for (int i = 0; i < 5; i++) {
		if (jnt_rag[i]) {
			mundo->DestroyJoint(jnt_rag[i]);
			jnt_rag[i] = nullptr;
		}
	}

	// Eliminar cuerpos
	for (int i = 0; i < 6; i++) {
		if (bdy_rag[i]) {
			mundo->DestroyBody(bdy_rag[i]);
			bdy_rag[i] = nullptr;
		}
		// Eliminar gráficos y actores también si querés limpiar memoria
		delete fig_rag[i];
		delete act_rag[i];
	}
}
