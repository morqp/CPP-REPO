#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class TextObject : public GameObject {
private:
    sf::Font& font;
    sf::Text text;
    std::string textStr;
    sf::Vector2f position;
public:
    TextObject(std::string identifier, sf::Font& font, std::string textStr) : GameObject(identifier), font(font), textStr(textStr) {
        text.setFont(font);
        text.setString(textStr);
    }
    ~TextObject() {}
    void update() override {}
    void render(sf::RenderWindow& window) override {
        window.draw(text);
    }
    std::string getTextStr() const {
        return textStr;
    }
    void setText(const std::string textStr) {
        this->textStr = textStr;
        text.setString(textStr);
    }
    void setCharacterSize(const int size) {
        text.setCharacterSize(size);
    }
    void setFillColor(const sf::Color color) {
        text.setFillColor(color);
    }
    void setPosition(const sf::Vector2f position) {
        this->position = position;
        text.setPosition(position);
    }
};