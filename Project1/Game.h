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
	Text txtNivelCompletado;
	bool mostrarNivelCompletado = false;
	float timerNivelCompletado = 0.f;
	bool gano = false;


	int nivelMaximo = 4;
	int disparos = 0;

	float fps, tiempoFrame, tiempo2;

	b2World* mundo1;
	Canion* canion = nullptr;
	SoundBuffer _sonidoDisparo; 
	Sound _disparo;
 
	//Contact listener
	MyContactListener* MCL = NULL;

	//obstaculos
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

	//ragdolls
	vector<Ragdoll*> ragdolls;

	//penduleitor
	Pendulo* pendulo = nullptr;

	//tritureitor
	Trituradora* trituradora = nullptr;

	//Arania!!!
	ZombieSpawner* zombieSpawner = nullptr;


	//interruptor para ganar el nivel
	Interruptor* interruptor = nullptr;

	//BACKGROUND
	Texture texBG;
	Sprite spriteBG;

	//TEXTOS
	Font font;
	Text txtTiempo;
	Text txtNivel;
	Text txtGameOver;
	Text txtDisparos;

	//Sizes para objetos
	b2Vec2 sizeLadrillos = b2Vec2(1.5f, 1.f);
	b2Vec2 sizeMetal = b2Vec2(1.5f, 1.f);
	b2Vec2 sizeNubes = b2Vec2(4.f, 1.5f);

	//TRANSICIONES
	enum class TransicionEstado { Nada, FadeOut, FadeIn };

	TransicionEstado transicion = TransicionEstado::Nada;
	float transTimer = 0.f;
	float transDuracion = 0.5f; // segundos

	RectangleShape overlayFade; // rect negro encima
	int nivelPendiente = 1;


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
	void LimpiarNivel();
	void CargarNivel(int n);
	void ClampMouseToWindow();
	
};

