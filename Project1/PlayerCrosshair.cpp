#pragma once 
#include "stdafx.h" 
#include "PlayerCrosshair.h"

using namespace sf;

PlayerCrosshair::PlayerCrosshair() {

	_crossTex.loadFromFile("../Images/pointer.png");
	_crossSprite.setTexture(_crossTex);
	Vector2u size = _crossTex.getSize();
	_crossSprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
	//_crossSprite.setRotation(90);
}

void PlayerCrosshair::Dibujar(RenderWindow* wnd) {
	wnd->draw(_crossSprite);
}

void PlayerCrosshair::Posicionar(float x, float y) {
	_crossSprite.setPosition(x, y);
}

Vector2f PlayerCrosshair::ObtenerPosicion() {
	return _crossSprite.getPosition();
}