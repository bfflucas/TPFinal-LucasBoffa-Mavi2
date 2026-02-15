#pragma once
#include "stdafx.h"
#include <iostream>
using namespace sf;
using namespace std;

class Button {
    RectangleShape _shape;
    Text _text;



public:
    Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size);

    void Dibujar(RenderWindow* wnd);

    bool isMouseOver(const sf::RenderWindow& wnd);

    void setText(const std::string& text);

    void setPosition(Vector2f& position);


};