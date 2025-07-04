#include "button.hpp"


Button::Button(std::string identifier, sf::Font& font, std::string buttonText, sf::Vector2f size, sf::Color color) : GameObject(identifier), font(font), buttonText(buttonText) {
	shape.setSize(size);
	shape.setFillColor(color);
	text.setFont(font);
	text.setString(buttonText);
}

Button::~Button() {}

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			onClick();
		}
	}
}

void Button::onClick() {}

void Button::update() {}

void Button::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(text);
}

void Button::setCharacterSize(const int size) {
	text.setCharacterSize(size);
}

void Button::setPosition(const sf::Vector2f position) {
	shape.setPosition(position);
	text.setCharacterSize(30);
	sf::FloatRect textBounds = text.getLocalBounds();
	sf::Vector2f centeredTextPos = position + sf::Vector2f((shape.getSize().x - textBounds.width) / 2.0f - textBounds.left, (shape.getSize().y - textBounds.height) / 2.0f - textBounds.top);
	text.setPosition(centeredTextPos);
}

