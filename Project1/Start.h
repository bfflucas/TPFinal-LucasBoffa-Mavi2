#pragma once
#include "PlayerCrosshair.h"
#include "Button.h"

using namespace sf;


class Start {
	PlayerCrosshair* _crosshair;
	RenderWindow* _wnd;
	SoundBuffer _buffer;
	Sound _sound;
	Button* _btnStart;
	Button* _btnTutorial;
	bool _start;
	Font _font;
	Text _text;
	bool _tutorial;
public:
	Start();
	void Loop();
	void ProcesarEventos();
	void Dibujar();
	void PlayMusic();
	bool GetStart();
	void IniciarJuego();
};