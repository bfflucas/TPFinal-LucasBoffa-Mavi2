#include "ZombieSpawner.h"
#include <cmath> 

static Texture texA;
static Texture texB;
static Texture texC;

ZombieSpawner::ZombieSpawner(b2World* mundo, const b2Vec2& posicion, Canion* c)
    : world(mundo), canion(c)
{

    static bool cargadas = false;

    if (!cargadas) {
        texA.loadFromFile("Images/spiderA.png");
        texB.loadFromFile("Images/spiderB.png");
        texC.loadFromFile("Images/spiderC.png");

        cargadas = true;
    }


    // 1) ANCLA (techo)
    b2BodyDef bdA;
    bdA.type = b2_staticBody;
    bdA.position = posicion; // este punto es donde cuelga la cuerda
    ancla = world->CreateBody(&bdA);

    // 2) ARANIA (spawner) - cuelga mas abajo
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = b2Vec2(posicion.x, posicion.y + largoCuerda);
    bd.fixedRotation = false;
    body = world->CreateBody(&bd);

    b2PolygonShape sh;
    sh.SetAsBox(2.f, 2.f);

    b2FixtureDef fd;
    fd.shape = &sh;
    fd.density = 1.f;
    fd.friction = 0.3f;
    fd.restitution = 0.0f;

    // IMPORTANTE: sensor para que no empuje/atasque las bolas al spawnear
    fd.isSensor = true;

    body->CreateFixture(&fd);

    // 3) DISTANCE JOINT = cuerda (mantiene distancia)
    b2DistanceJointDef djd;
    djd.bodyA = ancla;
    djd.bodyB = body;
    djd.collideConnected = false;

    // ancla en el techo
    djd.localAnchorA.Set(0.f, 0.f);

    // punto "arriba" del spawner (arriba del cubo)
    djd.localAnchorB.Set(0.f, -2.f);

    // largo fijo de la cuerda
    djd.length = largoCuerda;

    // para que no sea una barra dura (se siente como cuerda)
    //djd.frequencyHz = 2.5f;     // mas alto = mas tirante
    //djd.dampingRatio = 0.1f;    // amortiguacion
    // "cuerda" mas estable (segun version Box2D)
    djd.stiffness = 30.0f; // 10 - 80
    djd.damping = 3.0f;  //  0.5 - 10


    cuerdaJoint = (b2DistanceJoint*)world->CreateJoint(&djd);

    // 4) GRAFICO SPRAWNER
    figura = new RectangleShape();
    figura->setFillColor(Color::White);
    figura->setTexture(&texA);
    actor = new Actor(body, figura);

    // 5) GRAFICO CUERDA (rectangulo fino)
    fig_cuerda = new sf::RectangleShape();
    fig_cuerda->setFillColor(Color::White);
    fig_cuerda->setSize(Vector2f(1.f, grosorCuerda));
    fig_cuerda->setOrigin(0.f, grosorCuerda / 2.f);

    // 6) EMPUJON inicial para que empiece a hamacarse
    body->ApplyLinearImpulseToCenter(b2Vec2(30.f, 0.f), true);
}

ZombieSpawner::~ZombieSpawner() {
    for (auto* b : bolas) delete b;
    bolas.clear();

    delete actor; actor = nullptr;
    delete figura; figura = nullptr;

    delete fig_cuerda; fig_cuerda = nullptr;

    // orden seguro: joint -> body -> ancla
    if (cuerdaJoint && world) {
        world->DestroyJoint(cuerdaJoint);
        cuerdaJoint = nullptr;
    }

    if (body && world) {
        world->DestroyBody(body);
        body = nullptr;
    }

    if (ancla && world) {
        world->DestroyBody(ancla);
        ancla = nullptr;
    }
}

void ZombieSpawner::Actualizar(float dt) {
    timer += dt;
    tBalanceo += dt;

    if (timer >= cooldown) {
        timer = 0.f;
        SpawnBola();
    }

    // BALANCEO: fuerza horizontal suave va y viene
    // sinf da un movimiento continuo
    if (body) {
        body->SetAwake(true);

        float w = 2.f * 3.1415926f / periodoBalanceo;
        float s = std::sinf(w * tBalanceo);

        // fuerza horizontal
        body->ApplyForceToCenter(b2Vec2(fuerzaBalanceo * s, 0.f), true);
    }

    for (auto* b : bolas)
        b->Update(dt);

    // ===== ANIMACION SPIDER =====
    animTimer += dt;

    if (animTimer >= animDelay) {
        animTimer = 0.f;
        animFrame++;

        if (animFrame > 2)
            animFrame = 0;

        if (figura) {
            switch (animFrame) {
            case 0: figura->setTexture(&texA); break;
            case 1: figura->setTexture(&texB); break;
            case 2: figura->setTexture(&texC); break;
            }
        }
    }
}

void ZombieSpawner::SpawnBola() {
    if (!canion || !body || !world) return;

    // spawn un poco mas abajo del spawner para que caiga directo
    b2Vec2 p = body->GetPosition();
    b2Vec2 spawn = b2Vec2(p.x, p.y + 3.0f);

    Bola* b = new Bola(world, spawn, 0.8f, canion);
    bolas.push_back(b);
}

void ZombieSpawner::Dibujar(RenderWindow& wnd) {
    // 1) CUERDA (rectangulo)
    if (fig_cuerda && ancla && body) {
        b2Vec2 pA = ancla->GetPosition();
        b2Vec2 pB = body->GetWorldPoint(b2Vec2(0.f, -2.f));

        float dx = pB.x - pA.x;
        float dy = pB.y - pA.y;

        float len = sqrt(dx * dx + dy * dy);
        if (len > 0.0001f) {
            float ang = std::atan2(dy, dx) * 180.f / 3.1415926f;

            // que arranque un poco mas abajo del techo
            float ax = pA.x + (dx / len) * offsetInicioCuerda;
            float ay = pA.y + (dy / len) * offsetInicioCuerda;

            fig_cuerda->setSize(Vector2f(len - offsetInicioCuerda, grosorCuerda));
            fig_cuerda->setPosition(ax, ay);
            fig_cuerda->setRotation(ang);

            wnd.draw(*fig_cuerda);
        }
    }

    // 2) SPIDER
    if (actor) actor->dibujar(wnd);

    // 3) BOLAS
    for (auto* b : bolas)
        b->Dibujar(wnd);
}

void ZombieSpawner::BorrarBolas(Bola* b) {
    if (!b) return;

    for (int i = 0; i < (int)bolas.size(); i++) {
        if (bolas[i] == b) {
            delete bolas[i];
            bolas.erase(bolas.begin() + i);
            return;
        }
    }
}
