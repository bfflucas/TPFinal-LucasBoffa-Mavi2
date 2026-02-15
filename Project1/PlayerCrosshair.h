#pragma once 
#include "stdafx.h" 
using namespace sf;

class PlayerCrosshair {

	Texture _crossTex;
	Sprite _crossSprite;

public:

	PlayerCrosshair();

	void Dibujar(RenderWindow* wnd);

	void Posicionar(float x, float y);

	Vector2f ObtenerPosicion();

};