#include "Pendulo.h"

Pendulo::Pendulo(b2World* mundo, const b2Vec2& anchorPos) : world(mundo) {
    // Anchor estatico
    b2BodyDef bdA;
    bdA.type = b2_staticBody;
    bdA.position = anchorPos;
    anchor = world->CreateBody(&bdA);

    b2PolygonShape shA;
    shA.SetAsBox(0.3f, 0.3f);

    b2FixtureDef fdA;
    fdA.shape = &shA;
    fdA.userData.pointer = 3;
    anchor->CreateFixture(&fdA);

    // Bob dinamico (el peso)
    b2BodyDef bdB;
    bdB.type = b2_dynamicBody;
    bdB.position = b2Vec2(anchorPos.x, anchorPos.y + 6.f);
    bob = world->CreateBody(&bdB);

    b2PolygonShape shB;
    shB.SetAsBox(0.6f, 3.0f); // palo largo tipo martillo

    b2FixtureDef fdB;
    fdB.shape = &shB;
    fdB.density = 2.0f;
    fdB.friction = 0.5f;
    fdB.restitution = 0.1f;
    fdB.userData.pointer = 3; // o lo que quieras
    bob->CreateFixture(&fdB);

    // Revolute joint (bisagra)
    b2RevoluteJointDef rjd;
    rjd.bodyA = anchor;
    rjd.bodyB = bob;
    rjd.collideConnected = false;
    rjd.localAnchorA.Set(0.f, 0.f);
    rjd.localAnchorB.Set(0.f, -3.0f); // engancha el bob en su parte superior

    joint = (b2RevoluteJoint*)world->CreateJoint(&rjd);

    // Graficos
    figAnchor = new sf::RectangleShape();
    figAnchor->setFillColor(sf::Color::Blue);
    actAnchor = new Actor(anchor, figAnchor);

    figBob = new sf::RectangleShape();
    figBob->setFillColor(sf::Color::Yellow);
    actBob = new Actor(bob, figBob);
}

Pendulo::~Pendulo() {
    if (joint) { world->DestroyJoint(joint); joint = nullptr; }
    if (bob) { world->DestroyBody(bob); bob = nullptr; }
    if (anchor) { world->DestroyBody(anchor); anchor = nullptr; }

    delete actAnchor; delete figAnchor;
    delete actBob; delete figBob;
}

void Pendulo::Dibujar(sf::RenderWindow& wnd) {
    actAnchor->dibujar(wnd);
    actBob->dibujar(wnd);
}
