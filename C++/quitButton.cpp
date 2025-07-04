#include "quitButton.hpp"


QuitButton::QuitButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, sf::RenderWindow& window)
	: Button(identifier, font, "Quit", size, color), window(window) {
}

void QuitButton::onClick() {
	this->window.close();
}
