#pragma once
#include "PlayerCrosshair.h"
#include "Button.h"

class End {
	PlayerCrosshair* _crosshair;
	RenderWindow* _wnd;
	SoundBuffer _buffer;
	Sound _sound;
	Button* _btnReiniciar;
	Button* _btnSalir;
	bool _reiniciar;
	Font _font;
	Text _text, _textPuntos;
	int _puntos;

public:
	End();
	void Iniciar();
	void Loop();
	void ProcesarEventos();
	void Dibujar();
	void PlayMusic();
	bool GetReiniciar();
	void IniciarJuego();
	void SetPuntos(int valor);

};
