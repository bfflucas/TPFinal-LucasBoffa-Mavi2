#include "Includes.h"
#include "Actor.h"
#include "Canion.h"
#include "Ragdoll.h"
#include "MyContactListener.h"
#include "ObstaculoFijo.h"
#include "ObstaculoInmovil.h"
#include "ObstaculoMovil.h"
#include "Pendulo.h"
#include "Trituradora.h"
#include "Interruptor.h"
#include "ZombieSpawner.h"
#include <vector>


using namespace std;
using namespace sf;
class Game
{
private:
	RenderWindow* ventana1;
	View* camara1;

	Event* evento1;

	Time* tiempo1;
	Clock* reloj1; //para medir el tiempo

	//VARIABLES PARA GANAR O PERDER EL JUEGO
	int nivelActual = 1;
	float tiempoRestante = 60.f;
	bool gameOver = false;
	bool nivelSuperado = false;
	sf::Text txtNivelCompletado;
	bool mostrarNivelCompletado = false;
	float timerNivelCompletado = 0.f;

	int nivelMaximo = 4;


	float fps, tiempoFrame, tiempo2;

	b2World* mundo1;
	Canion* canion = nullptr;
	SoundBuffer _sonidoDisparo; 
	Sound _disparo;
 
	//Contact listener
	MyContactListener* MCL = NULL;


	vector<Obstaculo*> obstaculos;
	vector<ObstaculoMovil*> obstaculosMoviles;

	//Suelo

	RectangleShape* fig_suelo;

	b2Body* bdy_suelo;
	b2BodyDef bdydef_suelo;
	b2Fixture* fix_suelo;
	b2FixtureDef fixdef_suelo;

	Actor* act_suelo;


	//Techo

	RectangleShape* fig_techo;

	b2Body* bdy_techo;
	b2BodyDef bdydef_techo;
	b2Fixture* fix_techo;
	b2FixtureDef fixdef_techo;

	Actor* act_techo;

	//Pared Izquierda

	RectangleShape* fig_paredI;

	b2Body* bdy_paredI;
	b2BodyDef bdydef_paredI;
	b2Fixture* fix_paredI;
	b2FixtureDef fixdef_paredI;

	Actor* act_paredI;



	//Pared Derecha

	RectangleShape* fig_paredD;

	b2Body* bdy_paredD;
	b2BodyDef bdydef_paredD;
	b2Fixture* fix_paredD;
	b2FixtureDef fixdef_paredD;

	Actor* act_paredD;


	//Cañón
	b2Body* bdy_canion;
	b2BodyDef bdydef_canion;
	b2Fixture* fix_canion;
	b2FixtureDef fixdef_canion;

	RectangleShape* fig_canion;

	Actor* act_canion;

	//ragdolls
	vector<Ragdoll*> ragdolls;

	//penduleitor
	Pendulo* pendulo = nullptr;

	//tritureitor
	Trituradora* trituradora = nullptr;

	//Zombies!!!
	ZombieSpawner* zombieSpawner = nullptr;


	//interruptor para ganar el nivel
	Interruptor* interruptor = nullptr;


	//TEXTOS
	sf::Font font;
	sf::Text txtTiempo;
	sf::Text txtNivel;
	sf::Text txtGameOver;



public:

	// Constructores, destructores e inicializadores
	Game(Vector2i resolucion, std::string titulo);
	void set_camera();
	void iniciar_fisica();
	void iniciar_img();
	void actualizar_fisica();
	void procesar_eventos();
	void gameLoop();
	void dibujar();
	float deg2rad(float grados);
	void ReproducirDisparo();
	//void ReproducirChoque();
	void LimpiarNivel();
	void CargarNivel(int n);

	
};

