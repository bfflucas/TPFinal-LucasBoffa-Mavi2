#include "Game.h"

Game::Game(Vector2i resolucion, string titulo) {

	//sonido disparo
	_sonidoDisparo.loadFromFile("../Sounds/disparoCañon.wav");
	_disparo.setBuffer(_sonidoDisparo);
	  


	fps = 60;
	tiempoFrame = 1 / 60.f;
	tiempo2 = 0;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	set_camera();
	iniciar_fisica();
	iniciar_img();
	CargarNivel(2);

	evento1 = new Event;

	reloj1 = new Clock;
	tiempo1 = new Time;

	

	act_suelo = new Actor(bdy_suelo, fig_suelo);
	act_techo = new Actor(bdy_techo, fig_techo);
	act_paredI = new Actor(bdy_paredI, fig_paredI);
	act_paredD = new Actor(bdy_paredD, fig_paredD);

	
	act_canion = new Actor(bdy_canion, fig_canion);


	gameLoop();
}

void Game::set_camera() {

	camara1 = new View({ 5.f,5.f }, { 30.f,30.f }); //el centro, el tamaño
	camara1->move(53.5f, 83.5f);

	ventana1->setView(*camara1);
}

void Game::iniciar_fisica() {

	mundo1 = new b2World(b2Vec2(0.f, 9.8f));

	//Se crea el contact listener y se lo asigna al mundo
	MCL = new MyContactListener;
	mundo1->SetContactListener(MCL);

	//suelo
	bdydef_suelo.type = b2_staticBody;
	bdydef_suelo.position = b2Vec2(50.f, 103.f);
	bdy_suelo = mundo1->CreateBody(&bdydef_suelo);

	b2PolygonShape shp_suelo;
	shp_suelo.SetAsBox(50.f, 0.5f);

	fixdef_suelo.shape = &shp_suelo;
	fixdef_suelo.restitution = 0.f;
	fixdef_suelo.friction = 0.3f;
	fixdef_suelo.density = 1.f;
	fixdef_suelo.userData.pointer = 3;

	fix_suelo = bdy_suelo->CreateFixture(&fixdef_suelo);

	//techo
	bdydef_techo.type = b2_staticBody;
	bdydef_techo.position = b2Vec2(50.f, 73.5f);
	bdy_techo = mundo1->CreateBody(&bdydef_techo);

	b2PolygonShape shp_techo;
	shp_techo.SetAsBox(50.f, 0.5f);

	fixdef_techo.shape = &shp_techo;
	fixdef_techo.restitution = 0.f;
	fixdef_techo.friction = 0.3f;
	fixdef_techo.density = 1.f;
	fixdef_techo.userData.pointer = 3;

	fix_techo = bdy_techo->CreateFixture(&fixdef_techo);

	//paredI
	bdydef_paredI.type = b2_staticBody;
	bdydef_paredI.position = b2Vec2(43.5f, 83.5f);
	bdy_paredI = mundo1->CreateBody(&bdydef_paredI);

	b2PolygonShape shp_paredI;
	shp_paredI.SetAsBox(0.5f, 50.f);

	fixdef_paredI.shape = &shp_paredI;
	fixdef_paredI.restitution = 0.f;
	fixdef_paredI.friction = 0.3f;
	fixdef_paredI.density = 1.f;
	fixdef_paredI.userData.pointer = 3;

	fix_paredI = bdy_paredI->CreateFixture(&fixdef_paredI);


	//paredD
	bdydef_paredD.type = b2_staticBody;
	bdydef_paredD.position = b2Vec2(73.5f, 83.5f);
	bdy_paredD = mundo1->CreateBody(&bdydef_paredD);

	b2PolygonShape shp_paredD;
	shp_paredD.SetAsBox(0.5f, 50.f);

	fixdef_paredD.shape = &shp_paredD;
	fixdef_paredD.restitution = 0.f;
	fixdef_paredD.friction = 0.3f;
	fixdef_paredD.density = 1.f;
	fixdef_paredD.userData.pointer = 3;

	fix_paredD = bdy_paredD->CreateFixture(&fixdef_paredD);


	//Cañón   b2Vec2(47.5f, 98.5f);
	bdydef_canion.type = b2_staticBody;
	bdydef_canion.position = b2Vec2(45.5f, 100.5f);
	bdy_canion = mundo1->CreateBody(&bdydef_canion);

	b2PolygonShape shape_canion;
	shape_canion.SetAsBox(1.2f, 0.9f);


	fixdef_canion.shape = &shape_canion;
	fixdef_canion.density = 1.0f;
	fixdef_canion.restitution = 0.3f;
	fixdef_canion.friction = 0.3f;
	
	fix_canion = bdy_canion->CreateFixture(&fixdef_canion);

}

void Game::iniciar_img() {

	fig_suelo = new RectangleShape;
	fig_suelo->setFillColor(Color::Green);

	fig_techo = new RectangleShape;
	fig_techo->setFillColor(Color::Green);

	fig_paredI = new RectangleShape;
	fig_paredI->setFillColor(Color::Green);

	fig_paredD = new RectangleShape;
	fig_paredD->setFillColor(Color::Green);


	fig_canion = new RectangleShape;
	fig_canion->setFillColor(Color::Red);

}

void Game::actualizar_fisica() {

	mundo1->Step(tiempoFrame, 8, 8);
	mundo1->ClearForces();

	

	Vector2i posicion_m = Mouse::getPosition(*ventana1);
	Vector2f coordenadas_m = ventana1->mapPixelToCoords(posicion_m);

	// Calculamos el ángulo hacia el mouse
	float angulo_objetivo = atan2f(coordenadas_m.y - bdy_canion->GetPosition().y, coordenadas_m.x - bdy_canion->GetPosition().x);

	// Limitamos el ángulo (en radianes)
	float limite_min = deg2rad(-90); // -90°
	float limite_max = deg2rad(0);   // 0° (asumiendo que el cañón apunta a la derecha y sube cuando gira negativo)

	if (angulo_objetivo < limite_min) angulo_objetivo = limite_min;
	if (angulo_objetivo > limite_max) angulo_objetivo = limite_max;

	bdy_canion->SetTransform(bdy_canion->GetPosition(), angulo_objetivo);

	
	if (MCL->cuerpo_tocado) {
		if (MCL->cuerpo_tocado->GetType() == b2_kinematicBody) {
			MCL->cuerpo_tocado->SetType(b2_dynamicBody);

		}
		MCL->cuerpo_tocado = nullptr; // Limpiar para no hacer varias veces
		
	}

	// Borrar ragdoll si toco la trituradora
	if (MCL->ragdoll_a_borrar) {

		for (int i = 0; i < ragdolls.size(); i++) {

			if (ragdolls[i] == MCL->ragdoll_a_borrar) {

				delete ragdolls[i];                 // liberar memoria
				ragdolls.erase(ragdolls.begin() + i); // sacar del vector
				break;                              // salir del for
			}
		}

		MCL->ragdoll_a_borrar = nullptr;
	}


	for (auto* om : obstaculosMoviles) {
		om->Update();
	}

}

void Game::procesar_eventos() {

	while (ventana1->pollEvent(*evento1)) {
		switch (evento1->type) {
		case Event::Closed:

			LimpiarNivel();
			ventana1->close();

			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				bdy_canion->SetTransform(bdy_canion->GetPosition(), bdy_canion->GetAngle() - deg2rad(3));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				bdy_canion->SetTransform(bdy_canion->GetPosition(), bdy_canion->GetAngle() + deg2rad(3));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space)) {
				
			}
			break;

		case Event::MouseButtonPressed:

			Vector2i posicion_m;
			Vector2f coordenadas_m;
			float angle = bdy_canion->GetAngle(); // Ángulo de rotación en radianes

			ReproducirDisparo();

			// Calcular vector de dirección hacia donde apunta el cañón
			b2Vec2 direction(cos(angle), sin(angle));

			// Posición de disparo (punta del cañón)
			b2Vec2 spawnPos = { bdy_canion->GetPosition().x + cos(angle), bdy_canion->GetPosition().y + sin(angle) };
			//b2Vec2 spawnPos = bdy_canion->GetPosition() + b2Mul(0.3f, direction);

			posicion_m = Mouse::getPosition(*ventana1);
			coordenadas_m = ventana1->mapPixelToCoords(posicion_m);  //también ventana1->mapPixelToCoords( Mouse::getPosition(*ventana1));
			
			// Crear y guardar nueva ragdoll

			if (ragdolls.size() >= 10) {
				delete ragdolls.front();         // Eliminar el primero
				ragdolls.erase(ragdolls.begin()); // Sacarlo del vector
			}

			Ragdoll* nueva_rag = new Ragdoll({ spawnPos.x, spawnPos.y }, mundo1);

			// Aplicar fuerza en dirección al mouse
			nueva_rag->aplicar_fuerza({ coordenadas_m.x - bdy_canion->GetPosition().x, coordenadas_m.y - bdy_canion->GetPosition().y });

			// Agregarla al vector
			ragdolls.push_back(nueva_rag);

			break;
		}		
	}
}


void Game::gameLoop() {

	while (ventana1->isOpen()) {

		*tiempo1 = reloj1->getElapsedTime();
		if (tiempo2 + tiempoFrame < tiempo1->asSeconds()) {
			tiempo2 = tiempo1->asSeconds();

			ventana1->clear();
			procesar_eventos();
			actualizar_fisica();
			dibujar();
			ventana1->display();

		}
	}
}

void Game::dibujar() {

	act_suelo->dibujar(*ventana1);
	act_techo->dibujar(*ventana1);
	act_paredI->dibujar(*ventana1);
	act_paredD->dibujar(*ventana1);

	for (auto* obs : obstaculos) {
		obs->Dibujar(*ventana1);
	}

	for (auto* om : obstaculosMoviles) {
		om->Dibujar(*ventana1);
	}	

	if (pendulo) {
		pendulo->Dibujar(*ventana1);
	}


	if (trituradora) {
		trituradora->Dibujar(*ventana1);
	}

	for (auto& rag : ragdolls) {
		rag->Dibujar(*ventana1);
	}
	act_canion->dibujar(*ventana1);

	

}

float Game::deg2rad(float grados) {
	return grados * 3.14 / 180;
}

void Game::ReproducirDisparo() {
	_disparo.setVolume(80);
	_disparo.play();
}


void Game::CargarNivel(int n) {
	LimpiarNivel();

	if (n == 1) {
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(50.f, 85.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(60.f, 82.f), b2Vec2(1.5f, 1.f)));
	}
	else if (n == 2) {
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(55.f, 85.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(62.f, 90.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(60.f, 100.f), b2Vec2(1.5f, 1.f)));

		//le agrego el pendulo
		pendulo = new Pendulo(mundo1, b2Vec2(58.f, 76.f));

	}
	else if (n == 3) {
		// mas complicado
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(60.f, 82.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(60.f, 100.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(50.f, 85.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(65.f, 85.f), b2Vec2(1.5f, 1.f)));

		//le agrego una trituradora
		trituradora = new Trituradora(
			mundo1,
			b2Vec2(60.f, 102.f),  // posicion (cerca del piso)
			b2Vec2(6.f, 0.6f),    // halfSize (ancho, alto)
			99,                   // tag para el listener
			true                  // visible (false si no queres verla)
		);

	}

	//obstáculo Móvil
	// 
	obstaculosMoviles.push_back(
		new ObstaculoMovil(
			mundo1,
			b2Vec2(55.f, 92.f),   // posicion inicial
			b2Vec2(3.f, 0.4f),    // tamanio
			50.f,                 // limite minimo
			65.f,                 // limite maximo
			1.5f,                 // velocidad
			true                  // horizontal
		)
	);

}

void Game::LimpiarNivel() {

	// borrar ragdolls
	for (auto* r : ragdolls) delete r;
	ragdolls.clear();

	// borrar obstaculos del nivel
	for (auto* o : obstaculos) delete o;
	obstaculos.clear();
	for (auto* om : obstaculosMoviles) delete om;
	obstaculosMoviles.clear();

	if (pendulo) {
		delete pendulo;
		pendulo = nullptr;
	}


	if (trituradora) {
		delete trituradora;
		trituradora = nullptr;
	}

}


