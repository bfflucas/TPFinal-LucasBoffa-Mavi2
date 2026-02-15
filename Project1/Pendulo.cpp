#include "Pendulo.h"

Pendulo::Pendulo(b2World* mundo, const b2Vec2& anchorPos, float largo, float ancho, float densidad)
    : world(mundo)
{
    static Texture texBarra;
    static Texture texPunta;
    static bool cargadas = false;

    if (!cargadas) {
        texBarra.loadFromFile("../Images/cadena-pendulo.png");
        texPunta.loadFromFile("../Images/punta-pendulo.png");
        cargadas = true;
    }

    // 1) Anchor estatico
    b2BodyDef bdA;
    bdA.type = b2_staticBody;
    bdA.position = anchorPos;
    anchor = world->CreateBody(&bdA);

    b2PolygonShape shA;
    shA.SetAsBox(0.35f, 0.35f);

    b2FixtureDef fdA;
    fdA.shape = &shA;
    fdA.userData.pointer = 3;
    anchor->CreateFixture(&fdA);

    // 2) Barra (cuerpo largo) dinamica
    b2BodyDef bdC;
    bdC.type = b2_dynamicBody;
    bdC.position = b2Vec2(anchorPos.x, anchorPos.y + (largo * 0.5f));
    cuerpo = world->CreateBody(&bdC);

    b2PolygonShape shC;
    shC.SetAsBox(ancho * 0.5f, largo * 0.5f);

    b2FixtureDef fdC;
    fdC.shape = &shC;
    fdC.density = densidad;
    fdC.friction = 0.7f;
    fdC.restitution = 0.05f;
    fdC.userData.pointer = 3;
    cuerpo->CreateFixture(&fdC);

    // 3) Revolute joint (anchor - barra)
    b2RevoluteJointDef rjd;
    rjd.bodyA = anchor;
    rjd.bodyB = cuerpo;
    rjd.collideConnected = false;
    rjd.localAnchorA.Set(0.f, 0.f);
    rjd.localAnchorB.Set(0.f, -largo * 0.5f); // enganche arriba de la barra
    joint = (b2RevoluteJoint*)world->CreateJoint(&rjd);

    // 4) Punta (otro body cuadrado)
    float ladoPunta = ancho * 1.4f;

    b2BodyDef bdP;
    bdP.type = b2_dynamicBody;
    bdP.position = b2Vec2(anchorPos.x, anchorPos.y + largo + (ladoPunta * 0.5f));
    punta = world->CreateBody(&bdP);

    b2PolygonShape shP;
    shP.SetAsBox(ladoPunta * 0.5f, ladoPunta * 0.5f);

    b2FixtureDef fdP;
    fdP.shape = &shP;
    fdP.density = densidad; 
    fdP.friction = 0.7f;
    fdP.restitution = 0.05f;
    fdP.userData.pointer = 3;
    punta->CreateFixture(&fdP);

    // 5) Weld joint (barra - punta)
    b2WeldJointDef wjd;
    wjd.bodyA = cuerpo;
    wjd.bodyB = punta;
    wjd.collideConnected = false;

    // extremo inferior de la barra
    wjd.localAnchorA.Set(0.f, +largo * 0.5f);
    // parte superior de la punta
    wjd.localAnchorB.Set(0.f, -ladoPunta * 0.5f);

    wjd.stiffness = 80.0f;
    wjd.damping = 8.0f;

    jointPunta = (b2WeldJoint*)world->CreateJoint(&wjd);

    // 6) Graficos (Actor se encarga del size/origen/rotacion)
    figAnchor = new RectangleShape();
    figAnchor->setFillColor(Color::Blue);
    actAnchor = new Actor(anchor, figAnchor);

    figCuerpo = new RectangleShape();
    figCuerpo->setTexture(&texBarra);
    figCuerpo->setFillColor(Color::White);
    actCuerpo = new Actor(cuerpo, figCuerpo);

    figPunta = new RectangleShape();
    figPunta->setTexture(&texPunta);
    figPunta->setFillColor(Color::White);
    actPunta = new Actor(punta, figPunta);
}

Pendulo::~Pendulo() {

    // joints primero
    if (jointPunta && world) { world->DestroyJoint(jointPunta); jointPunta = nullptr; }
    if (joint && world) { world->DestroyJoint(joint);      joint = nullptr; }

    // bodies
    if (punta && world) { world->DestroyBody(punta);  punta = nullptr; }
    if (cuerpo && world) { world->DestroyBody(cuerpo); cuerpo = nullptr; }
    if (anchor && world) { world->DestroyBody(anchor); anchor = nullptr; }

    // actores + figuras
    delete actAnchor; actAnchor = nullptr;
    delete figAnchor; figAnchor = nullptr;

    delete actCuerpo; actCuerpo = nullptr;
    delete figCuerpo; figCuerpo = nullptr;

    delete actPunta; actPunta = nullptr;
    delete figPunta; figPunta = nullptr;
}

void Pendulo::IniciarMovimiento(float impulsoX) {
    if (!cuerpo) return;

    cuerpo->ApplyLinearImpulseToCenter(b2Vec2(impulsoX, 0.f), true);
    cuerpo->ApplyAngularImpulse(impulsoX * 0.5f, true);
}

void Pendulo::Dibujar(RenderWindow& wnd) {
    if (actAnchor) actAnchor->dibujar(wnd);
    if (actCuerpo) actCuerpo->dibujar(wnd);
    if (actPunta)  actPunta->dibujar(wnd);
}
