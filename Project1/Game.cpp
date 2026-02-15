#include "Game.h"

Game::Game(Vector2i resolucion, string titulo) {
	//============BACKGROUND======================
	texBG.loadFromFile("../Images/background1.png");
	texBG.setSmooth(false);
	spriteBG.setTexture(texBG);

	// origen al centro de la imagen
	sf::Vector2u s = texBG.getSize();
	spriteBG.setOrigin(s.x * 0.5f, s.y * 0.5f);

	//============SONIDO DISPARO=================
	_sonidoDisparo.loadFromFile("../Sounds/disparoCañon.wav");
	_disparo.setBuffer(_sonidoDisparo);
	  

	//===============TIEMPO===================
	fps = 60;
	tiempoFrame = 1 / 60.f;
	tiempo2 = 0;

	//==============WINDOW================
	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	set_camera();

	// ===== AJUSTAR BACKGROUND A LA VIEW =====
	sf::Vector2u ts = texBG.getSize();
	sf::Vector2f viewSize = camara1->getSize();

	// escala directa a la camara
	spriteBG.setScale(
		viewSize.x / ts.x,
		viewSize.y / ts.y
	);

	iniciar_fisica();
	iniciar_img();

	nivelActual = 1;
	tiempoRestante = 60.f;
	gameOver = false;
	nivelSuperado = false;
	CargarNivel(nivelActual);

	evento1 = new Event;

	reloj1 = new Clock;
	tiempo1 = new Time;

	

	act_suelo = new Actor(bdy_suelo, fig_suelo);
	act_techo = new Actor(bdy_techo, fig_techo);
	act_paredI = new Actor(bdy_paredI, fig_paredI);
	act_paredD = new Actor(bdy_paredD, fig_paredD);

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
	fixdef_suelo.userData.pointer = 30;

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

	//CANION   b2Vec2(47.5f, 98.5f);
	canion = new Canion(mundo1, b2Vec2(45.5f, 100.5f));
}

void Game::iniciar_img() {

	Color color = Color(70, 70, 70);

	fig_suelo = new RectangleShape;
	fig_suelo->setFillColor(color);

	fig_techo = new RectangleShape;
	fig_techo->setFillColor(color);

	fig_paredI = new RectangleShape;
	fig_paredI->setFillColor(color);

	fig_paredD = new RectangleShape;
	fig_paredD->setFillColor(color);



	if (!font.loadFromFile("../Fonts/SpicyRice-Regular.ttf")) {
		
	}

	// TIMER
	txtTiempo.setFont(font);
	txtTiempo.setCharacterSize(24);
	txtTiempo.setFillColor(sf::Color::White);
	txtTiempo.setPosition(30.f, 30.f); // en pantalla (HUD)
	txtTiempo.setString("Tiempo: 60");

	//NIVEL
	txtNivel.setFont(font);
	txtNivel.setCharacterSize(24);
	txtNivel.setFillColor(sf::Color::Magenta);
	txtNivel.setPosition(30.f, 55.f);
	txtNivel.setString("Nivel: " + std::to_string(nivelActual));

	// GAME OVER
	txtGameOver.setFont(font);
	txtGameOver.setCharacterSize(64);
	txtGameOver.setFillColor(sf::Color::Red);
	txtGameOver.setString("GAME OVER");

	//PASAJE DE NIVELES
	txtNivelCompletado.setFont(font);
	txtNivelCompletado.setCharacterSize(48);
	txtNivelCompletado.setFillColor(sf::Color::Yellow);
	txtNivelCompletado.setString("NIVEL COMPLETADO");


	// DISPAROS
	txtDisparos.setFont(font);
	txtDisparos.setCharacterSize(24);
	txtDisparos.setFillColor(sf::Color::White);
	txtDisparos.setPosition(400.f, 30.f);

	// arriba a la derecha
	txtDisparos.setString("Disparos: 0");

	//TRANSICIONES
	overlayFade.setFillColor(sf::Color(0, 0, 0, 0));
	overlayFade.setSize(sf::Vector2f(
		(float)ventana1->getSize().x,
		(float)ventana1->getSize().y
	));
	overlayFade.setPosition(0.f, 0.f);




}

void Game::actualizar_fisica() {


	// --- TRANSICION: si esta activa, solo animamos overlay y salimos ---
	if (transicion != TransicionEstado::Nada) {

		transTimer += tiempoFrame;
		float t = transTimer / transDuracion;
		if (t > 1.f) t = 1.f;

		if (transicion == TransicionEstado::FadeOut) {
			int a = (int)(255.f * t);
			overlayFade.setFillColor(sf::Color(0, 0, 0, a));

			if (t >= 1.f) {
				// tapo todo - cambio nivel aca
				nivelActual = nivelPendiente;
				tiempoRestante = 60.f;
				CargarNivel(nivelActual);

				// ahora destapar
				transicion = TransicionEstado::FadeIn;
				transTimer = 0.f;
			}
		}
		else { // FadeIn
			int a = (int)(255.f * (1.f - t));
			overlayFade.setFillColor(sf::Color(0, 0, 0, a));

			if (t >= 1.f) {
				overlayFade.setFillColor(sf::Color(0, 0, 0, 0));
				transicion = TransicionEstado::Nada;
			}
		}
		return; 
	}


	mundo1->Step(tiempoFrame, 8, 8);
	mundo1->ClearForces();


	if (mostrarNivelCompletado) {
		timerNivelCompletado -= tiempoFrame;
		if (timerNivelCompletado <= 0.f) {
			mostrarNivelCompletado = false;
			timerNivelCompletado = 0.f;
		}
		return;
	}

	// si gano o gameOver, no corre la fisica del juego ni el timer
	if (gano || gameOver) return;

	//CONTADOR DE TIEMPO
	tiempoRestante -= tiempoFrame;


	if (tiempoRestante <= 0.f) {
		tiempoRestante = 0.f;
		gameOver = true;

		txtGameOver.setString(
			"GAME OVER\n\n"
			"R - Reiniciar\n"
			"ESC - Salir"
		);
		return;
	}


	Vector2i posicion_m = Mouse::getPosition(*ventana1);
	Vector2f coordenadas_m = ventana1->mapPixelToCoords(posicion_m);
	if (canion)
		canion->UpdateAimMouse(*ventana1);

	// Calculamos el angulo hacia el mouse
	if (canion && canion->GetBody()) {
		float angle = canion->GetAngle();
		b2Vec2 pos = canion->GetBody()->GetPosition();
	}
	
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
	//BORRA ZOMBIEEEEEEE
	if (MCL->bola_a_borrar) {
		if (zombieSpawner) {
			zombieSpawner->BorrarBolas(MCL->bola_a_borrar);
		}
		MCL->bola_a_borrar = nullptr;
	}


	for (auto* om : obstaculosMoviles) {
		om->Update();
	}

	if (trituradora) {
		trituradora->Actualizar();
	}

	if (zombieSpawner)
		zombieSpawner->Actualizar(tiempoFrame);

	// Penalizacion por trituradora (resta tiempo una sola vez)
	if (MCL->penalizar_tiempo) {
		tiempoRestante -= 5.f;             // saca 5 segundos
		if (tiempoRestante < 0.f) tiempoRestante = 0.f;
		MCL->penalizar_tiempo = false;     // apagar para que no reste infinito
	}

	//PARA SUPERAR NIVELES
	if (MCL->nivel_superado) {
		MCL->nivel_superado = false;

		// mensaje 1 segundo
		mostrarNivelCompletado = true;
		timerNivelCompletado = 1.0f;

		nivelPendiente = nivelActual + 1;

		// si supero el ultimo nivel
		if (nivelPendiente > nivelMaximo) {
			gano = true;          
			gameOver = true;     
			txtGameOver.setString(
				"GANASTE\n\n"
				"R - Reiniciar\n"
				"ESC - Salir"
			);
			return;
		}

		// arranca fade-out
		transicion = TransicionEstado::FadeOut;
		transTimer = 0.f;

		return; // corta este frame
	}


	//CONTADOR DE TIEMPO
	int t = (int)tiempoRestante;
	if (t < 0) t = 0;
	txtTiempo.setString("Tiempo: " + std::to_string(t));
	// Color del timer
	if (t <= 15) txtTiempo.setFillColor(sf::Color::Red);
	else txtTiempo.setFillColor(sf::Color::White);

	// Texto nivel
	txtNivel.setString("Nivel: " + std::to_string(nivelActual));
	// Texto disparos
	txtDisparos.setString("Disparos: " + std::to_string(disparos));

}

void Game::procesar_eventos() {

	while (ventana1->pollEvent(*evento1)) {
		switch (evento1->type) {
		case Event::Closed:

			LimpiarNivel();
			ventana1->close();

			break;
		case Event::KeyPressed:
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				LimpiarNivel();
				ventana1->close();
				break;
			}

			if (Keyboard::isKeyPressed(Keyboard::R) && gameOver) {

				// 1) Reset flags de fin de juego
				gameOver = false;
				gano = false;              
				nivelActual = 1;
				tiempoRestante = 60.f;
				disparos = 0;

				// 2) Reset transicion 
				transicion = TransicionEstado::Nada;
				transTimer = 0.f;
				nivelPendiente = 1;
				overlayFade.setFillColor(sf::Color(0, 0, 0, 0));

				// 3) Reset mensaje nivel completado
				mostrarNivelCompletado = false;
				timerNivelCompletado = 0.f;

				// 4) Reset flags del contact listener
				MCL->nivel_superado = false;
				MCL->ragdoll_a_borrar = nullptr;
				MCL->cuerpo_tocado = nullptr;
				MCL->penalizar_tiempo = false;
				MCL->bola_a_borrar = nullptr;   

				// 5) Cargar nivel 1 limpio
				CargarNivel(nivelActual);

				break;
			}
		}

		case Event::MouseButtonPressed:
		{
			if (gameOver) break;
			if (!canion || !canion->GetBody()) break;

			float angle = canion->GetAngle();
			b2Vec2 pos = canion->GetBody()->GetPosition();
			b2Vec2 spawnPos = { pos.x + cos(angle), pos.y + sin(angle) };

			ReproducirDisparo();

			Vector2i posicion_m = Mouse::getPosition(*ventana1);
			Vector2f coordenadas_m = ventana1->mapPixelToCoords(posicion_m);

			if (ragdolls.size() >= 10) {
				delete ragdolls.front();
				ragdolls.erase(ragdolls.begin());
			}

			Ragdoll* nueva_rag = new Ragdoll({ spawnPos.x, spawnPos.y }, mundo1);
			disparos++;


			nueva_rag->aplicar_fuerza({ coordenadas_m.x - pos.x, coordenadas_m.y - pos.y });

			ragdolls.push_back(nueva_rag);
			break;
		}

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
			ClampMouseToWindow();
			actualizar_fisica();
			dibujar();
			ventana1->display();

		}
	}
}

void Game::dibujar() {

	// Fondo centrado en la camara
	spriteBG.setPosition(camara1->getCenter());
	ventana1->draw(spriteBG);

	act_suelo->dibujar(*ventana1);
	act_techo->dibujar(*ventana1);
	act_paredI->dibujar(*ventana1);
	act_paredD->dibujar(*ventana1);

	if (canion) canion->Dibujar(*ventana1);

	if (interruptor) interruptor->Dibujar(*ventana1);

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

	if (zombieSpawner)
		zombieSpawner->Dibujar(*ventana1);

	for (auto& rag : ragdolls) {
		rag->Dibujar(*ventana1);
	}
	

	//HUD
	sf::View vistaActual = ventana1->getView();
	ventana1->setView(ventana1->getDefaultView());

	ventana1->draw(txtTiempo);
	ventana1->draw(txtNivel);
	ventana1->draw(txtDisparos);


	if (mostrarNivelCompletado) {
		sf::FloatRect b = txtNivelCompletado.getLocalBounds();
		txtNivelCompletado.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
		txtNivelCompletado.setPosition(
			ventana1->getSize().x / 2.f,
			ventana1->getSize().y / 2.f - 80.f
		);
		ventana1->draw(txtNivelCompletado);
	}

	ventana1->draw(overlayFade);


	if (gameOver) {
		// Centrar "GAME OVER"
		sf::FloatRect bounds = txtGameOver.getLocalBounds();
		txtGameOver.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		txtGameOver.setPosition(
			ventana1->getSize().x / 2.f,
			ventana1->getSize().y / 2.f
		);

		ventana1->draw(txtGameOver);
	}

	ventana1->setView(vistaActual);


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

	/*  LIMITES DE LA ESCENA:
	    X min = 58.5 - 15 = 43.5
		X max = 58.5 + 15 = 73.5
		Y min = 88.5 - 15 = 73.5
		Y max = 88.5 + 15 = 103.5*/

	//OBSTACULO FIJO = kinematic  OBSTACULO INMOVIL = static
	switch (n) {
	case 1:
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(70.f, 80.f), sizeLadrillos));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(50.f, 80.f), sizeLadrillos));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(60.f, 88.f), sizeLadrillos));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(65.f, 84.f), sizeLadrillos));
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(60.f, 82.f), sizeMetal));
		//obstáculo Móvil 
		obstaculosMoviles.push_back(
			new ObstaculoMovil(
				mundo1,
				b2Vec2(55.f, 90.f),   // posicion inicial
				sizeNubes,            // tamanio
				50.f,                 // limite minimo
				65.f,                 // limite maximo
				1.5f,                 // velocidad
				true                  // horizontal
			)
		);
		interruptor = new Interruptor(mundo1, b2Vec2(70.f, 80.f), b2Vec2(0.8f, 0.8f));
		break;
	case 2:
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(49.f, 85.f), sizeLadrillos));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(64.f, 87.f), sizeLadrillos));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(66.f, 78.f), sizeLadrillos)); //el del interruptor
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(66.f, 90.f), sizeLadrillos));

		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(70.5f, 92.f), sizeMetal));
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(47.f, 81.f), sizeMetal));

		obstaculosMoviles.push_back(
			new ObstaculoMovil(
				mundo1,
				b2Vec2(55.f, 93.f),   // posicion inicial
				sizeNubes,            // tamanio
				50.f,                 // limite minimo
				65.f,                 // limite maximo
				1.5f,                 // velocidad
				true                  // horizontal
			)
		);

		interruptor = new Interruptor(mundo1, b2Vec2(66.f, 78.f), b2Vec2(0.8f, 0.8f));

		// Pendulo(mundo, b2Vec2& anchorPos,largo, ancho,densidad);
		pendulo = new Pendulo(mundo1, b2Vec2(58.f, 76.f), 14.0f, 0.7f, 1.0f);
		pendulo->IniciarMovimiento(10.0f);
		break;
	case 3:
		// mas complicado
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(69.f, 87.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoInmovil(mundo1, b2Vec2(47.f, 85.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(63.f, 85.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(53.f, 85.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(55.f, 89.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(52.f, 76.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(68.f, 77.f), b2Vec2(1.5f, 1.f)));

		obstaculosMoviles.push_back(
			new ObstaculoMovil(
				mundo1,
				b2Vec2(55.f, 81.f),   // posicion inicial
				sizeNubes,            // tamanio
				50.f,                 // limite minimo
				65.f,                 // limite maximo
				1.5f,                 // velocidad
				true                  // horizontal
			)
		);

		interruptor = new Interruptor(mundo1, b2Vec2(52.f, 76.f), b2Vec2(0.8f, 0.8f));

		// trituradora
		trituradora = new Trituradora(
			mundo1,
			b2Vec2(60.f, 92.f),   // posicion inicial
			b2Vec2(5.f, 0.8f),     // halfSize
			true,                  // visible
			50.f,                  // limiteMinX
			63.f,                  // limiteMaxX
			9.f                   // velocidad
		);
		break;
	case 4:
		zombieSpawner = new ZombieSpawner(
			mundo1,
			{ 60.f, 73.5f }, // arriba
			canion
		);

		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(52.f, 76.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(50.f, 80.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(68.f, 80.f), b2Vec2(1.5f, 1.f)));
		obstaculos.push_back(new ObstaculoFijo(mundo1, b2Vec2(70.f, 90.f), b2Vec2(1.5f, 1.f)));
		obstaculosMoviles.push_back(
			new ObstaculoMovil(
				mundo1,
				b2Vec2(55.f, 93.f),   // posicion inicial
				sizeNubes,            // tamanio
				50.f,                 // limite minimo
				65.f,                 // limite maximo
				1.5f,                 // velocidad
				true,                  // horizontal
				40
			)
		);

		interruptor = new Interruptor(mundo1, b2Vec2(52.f, 76.f), b2Vec2(0.8f, 0.8f));
		break;

	}
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

	//borra objetos especiales
	if (pendulo) {
		delete pendulo;
		pendulo = nullptr;
	}

	if (trituradora) {
		delete trituradora;
		trituradora = nullptr;
	}

	if (zombieSpawner) {
		delete zombieSpawner;
		zombieSpawner = nullptr;
	}

	if (interruptor) {
		delete interruptor;
		interruptor = nullptr;
	}

	//Limpiar flags
	MCL->ragdoll_a_borrar = nullptr;
	MCL->nivel_superado = false;
	MCL->cuerpo_tocado = nullptr;
}

void Game::ClampMouseToWindow()
{
	Vector2i mousePos = sf::Mouse::getPosition(*ventana1);

	int width = ventana1->getSize().x;
	int height = ventana1->getSize().y;

	bool cambio = false;

	if (mousePos.x < 0) {
		mousePos.x = 0;
		cambio = true;
	}
	if (mousePos.x > width - 1) {
		mousePos.x = width - 1;
		cambio = true;
	}

	if (mousePos.y < 0) {
		mousePos.y = 0;
		cambio = true;
	}
	if (mousePos.y > height - 1) {
		mousePos.y = height - 1;
		cambio = true;
	}

	// Solo seteamos si realmente se salio
	if (cambio)
		Mouse::setPosition(mousePos, *ventana1);
}
