#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"



Button::Button(const string& text, const Font& font, unsigned int characterSize, const Vector2f& position, const Vector2f& size)
    : _text(text, font, characterSize), _shape(size) {
    // Configurar el rectángulo del botón
    _shape.setPosition(position);
    _shape.setFillColor(Color::Blue); // Color de fondo del botón
    _shape.setOutlineThickness(2);
    _shape.setOutlineColor(Color::White);

    // Configurar el texto del botón
    _text.setFillColor(Color::White);
    _text.setPosition(position.x + (size.x - _text.getLocalBounds().width) / 2,
        position.y + (size.y - _text.getLocalBounds().height) / 2);
}

void Button::Dibujar(RenderWindow* wnd) {
    wnd->draw(_shape);
    wnd->draw(_text);
}

bool Button::isMouseOver(const RenderWindow& wnd) {
    Vector2i mousePos = Mouse::getPosition(wnd); // Obtener posición del mouse relativa a la ventana
    return _shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setText(const string& text) {
    _text.setString(text);
}

void Button::setPosition(Vector2f& position) {
    _shape.setPosition(position);
    _text.setPosition(position.x + (_shape.getSize().x - _text.getLocalBounds().width) / 2,
        position.y + (_shape.getSize().y - _text.getLocalBounds().height) / 2);
}

