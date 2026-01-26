#include "Actor.h"



//La clase Actor vincula un cuerpo fisico de Box2D con su representacion grafica en SFML.
// Se encarga de leer la posicion y rotacion del cuerpo fisico en cada frame y actualizar la figura grafica correspondiente,
// garantizando que la simulacion fisica y la visualizacion se mantengan sincronizadas.

Actor::Actor(b2Body* cuerpo, RectangleShape* figura) : bdy_actor(cuerpo), fig_actor(figura) 
{

	if (!bdy_actor) {
		throw std::runtime_error("Actor: cuerpo (b2Body*) es nullptr");
	}
	if (!fig_actor) {
		throw std::runtime_error("Actor: figura (RectangleShape*) es nullptr");
	}

	posicion = bdy_actor->GetPosition();

	

	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	//en nuestro caso usamos un solo fixture
	for (b2Fixture* i = bdy_actor->GetFixtureList(); i; i = i->GetNext()) {
		dimensiones = i->GetAABB(0);
	}

	
	fig_actor->setSize({ dimensiones.GetExtents().x * 2,dimensiones.GetExtents().y * 2 });
	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);
	fig_actor->setPosition(posicion.x, posicion.y);
}

void Actor::dibujar(RenderWindow& ventana) {
	posicion = bdy_actor->GetPosition();

	fig_actor->setPosition(posicion.x, posicion.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));

	ventana.draw(*fig_actor);
}

float Actor::rad2deg(float radianes) {

	//3.14____________180
	//radian__________x


	return radianes * 180 / 3.14;
}