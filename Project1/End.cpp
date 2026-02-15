#include "End.h"

End::End() {

	_buffer.loadFromFile("../Sounds/temaInicio.mp3");
	_sound.setBuffer(_buffer);
	_font.loadFromFile("../Fuentes/Hyperspace.ttf");
	_text.setFont(_font);
	_textPuntos.setFont(_font);

	_text.setString("GAME OVER");

}

void End::Iniciar() {
	_wnd = new RenderWindow(VideoMode(1280, 1080), "Asteroids");
	_wnd->setMouseCursorVisible(false);
	PlayMusic();
	_crosshair = new PlayerCrosshair();
	_textPuntos.setCharacterSize(80);
	_textPuntos.setPosition(90, 430);
	_textPuntos.setString("Conseguiste " + to_string(_puntos) + " puntos!!");
	_text.setCharacterSize(200);
	_text.setPosition(100, 150);
	_btnReiniciar = new Button("REINICIAR", _font, 50, Vector2f(450, 600), Vector2f(300, 150));    //string& text, Font& font, unsigned int characterSize, Vector2f& position, Vector2f& size
	_btnSalir = new Button("SALIR", _font, 50, Vector2f(450, 850), Vector2f(300, 150));
}

void End::ProcesarEventos() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Event evt;
	while (_wnd->pollEvent(evt)) {
		if (evt.type == Event::Closed) {
			_wnd->close();
		}
		if (evt.type == Event::MouseMoved) {
			_crosshair->Posicionar(evt.mouseMove.x, evt.mouseMove.y);
		}
		if (evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left) {
			if (_btnReiniciar->isMouseOver(*_wnd)) {
				IniciarJuego();
			}
		}
		if (evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left) {
			if (_btnSalir->isMouseOver(*_wnd)) {
				_reiniciar = false;
				_wnd->close();
			}
		}
	}
}

void End::Loop() {
	Iniciar();
	while (_wnd->isOpen()) {
		ProcesarEventos();
		Dibujar();
	}
}


void End::Dibujar() {
	_wnd->clear();
	_btnReiniciar->Dibujar(_wnd);
	_btnSalir->Dibujar(_wnd);
	_crosshair->Dibujar(_wnd);
	_wnd->draw(_text);
	_wnd->draw(_textPuntos);
	_wnd->display();
}

void End::PlayMusic() {
	_sound.setVolume(60);
	_sound.setLoop(true);
	_sound.play();
}

void End::IniciarJuego() {
	_reiniciar = true;
	_sound.stop();
	_wnd->close();
}

bool End::GetReiniciar() {
	return _reiniciar;
}

void End::SetPuntos(int valor) {
	_puntos = valor;
}