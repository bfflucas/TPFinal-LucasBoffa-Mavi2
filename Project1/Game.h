#include "Includes.h"
#include "Actor.h"
#include "Ragdoll.h"
#include "MyContactListener.h"
#include "ObstaculoFijo.h"
#include "ObstaculoInmovil.h"
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

	float fps, tiempoFrame, tiempo2;

	b2World* mundo1;

	SoundBuffer _sonidoDisparo; 
	Sound _disparo;
 
	//Contact listener
	MyContactListener* MCL = NULL;


	vector<Obstaculo*> obstaculos;

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


	// obstáculo fijo
	RectangleShape* fig_obstaculoF;

	b2Body* bdy_obstaculoF;
	b2BodyDef bdydef_obstaculoF;
	b2Fixture* fix_obstaculoF;
	b2FixtureDef fixdef_obstaculoF;

	Actor* act_obstaculoF;

	// obstáculo fijo 2
	RectangleShape* fig_obstaculoF2;

	b2Body* bdy_obstaculoF2;
	b2BodyDef bdydef_obstaculoF2;
	b2Fixture* fix_obstaculoF2;
	b2FixtureDef fixdef_obstaculoF2;

	Actor* act_obstaculoF2;

	// obstáculo inmóvil 1
	RectangleShape* fig_obstaculoI;

	b2Body* bdy_obstaculoI;
	b2BodyDef bdydef_obstaculoI;
	b2Fixture* fix_obstaculoI;
	b2FixtureDef fixdef_obstaculoI;

	Actor* act_obstaculoI;

	// obstáculo inmóvil 2
	RectangleShape* fig_obstaculoI2;

	b2Body* bdy_obstaculoI2;
	b2BodyDef bdydef_obstaculoI2;
	b2Fixture* fix_obstaculoI2;
	b2FixtureDef fixdef_obstaculoI2;

	Actor* act_obstaculoI2;

	//obstáculo móvil
	float desplazamiento = 0.03f;
	float rotacion = 0.015f;
	RectangleShape* fig_obstaculoM;

	b2Body* bdy_obstaculoM;
	b2BodyDef bdydef_obstaculoM;
	b2Fixture* fix_obstaculoM;
	b2FixtureDef fixdef_obstaculoM;

	Actor* act_obstaculoM;



	//Cañón
	b2Body* bdy_canion;
	b2BodyDef bdydef_canion;
	b2Fixture* fix_canion;
	b2FixtureDef fixdef_canion;

	RectangleShape* fig_canion;

	Actor* act_canion;

	//ragdolls


	vector<Ragdoll*> ragdolls;


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
	void ReproducirChoque();
	
	
};

