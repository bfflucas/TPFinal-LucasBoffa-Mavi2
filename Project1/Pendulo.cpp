#include "Pendulo.h"

Pendulo::Pendulo(b2World* mundo, const b2Vec2& anchorPos, float largo, float ancho, float densidad)
    : world(mundo)
{
    // 1) Anchor estatico (un cuadrito donde cuelga)
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

    // 2) Cuerpo dinamico colgante (LARGO Y PESADO)
    b2BodyDef bdC;
    bdC.type = b2_dynamicBody;

    // Lo ubicamos debajo del anchor, centrado
    bdC.position = b2Vec2(anchorPos.x, anchorPos.y + (largo * 0.5f));
    cuerpo = world->CreateBody(&bdC);

    b2PolygonShape shC;
    // SetAsBox(halfWidth, halfHeight)
    shC.SetAsBox(ancho * 0.5f, largo * 0.5f);

    b2FixtureDef fdC;
    fdC.shape = &shC;
    fdC.density = densidad;     // MAS PESADO
    fdC.friction = 0.7f;
    fdC.restitution = 0.05f;
    fdC.userData.pointer = 3;
    cuerpo->CreateFixture(&fdC);

    // 3) Revolute joint (bisagra en el punto del anchor)
    b2RevoluteJointDef rjd;
    rjd.bodyA = anchor;
    rjd.bodyB = cuerpo;
    rjd.collideConnected = false;

    // punto del joint en coordenadas del mundo (el mismo anchorPos)
    rjd.localAnchorA.Set(0.f, 0.f);

    // en el cuerpo: enganchamos en la parte de arriba del rectangulo
    rjd.localAnchorB.Set(0.f, -largo * 0.5f);

    joint = (b2RevoluteJoint*)world->CreateJoint(&rjd);

    // 4) Graficos
    figAnchor = new sf::RectangleShape();
    figAnchor->setFillColor(sf::Color::Blue);
    actAnchor = new Actor(anchor, figAnchor);

    figCuerpo = new sf::RectangleShape();
    figCuerpo->setFillColor(sf::Color(180, 180, 180)); // gris metal
    actCuerpo = new Actor(cuerpo, figCuerpo);
}

Pendulo::~Pendulo() {

    // destruir joint antes que bodies
    if (joint) { world->DestroyJoint(joint); joint = nullptr; }

    if (cuerpo) { world->DestroyBody(cuerpo); cuerpo = nullptr; }
    if (anchor) { world->DestroyBody(anchor); anchor = nullptr; }

    delete actAnchor; actAnchor = nullptr;
    delete figAnchor; figAnchor = nullptr;

    delete actCuerpo; actCuerpo = nullptr;
    delete figCuerpo; figCuerpo = nullptr;
}

void Pendulo::IniciarMovimiento(float impulsoX) {
    if (!cuerpo) return;

    // Impulso lateral aplicado en el centro
    cuerpo->ApplyLinearImpulseToCenter(b2Vec2(impulsoX, 0.f), true);

    // Opcional: un toque de giro
    cuerpo->ApplyAngularImpulse(impulsoX * 0.5f, true);
}


void Pendulo::Dibujar(sf::RenderWindow& wnd) {
    if (actAnchor) actAnchor->dibujar(wnd);
    if (actCuerpo) actCuerpo->dibujar(wnd);
}
