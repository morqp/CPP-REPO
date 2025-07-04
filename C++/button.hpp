#pragma once

#include "gameObject.hpp"
#include "sceneHandler.hpp"
#include "enemy.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>


class Button : public GameObject {
private:
	sf::Text text;
	sf::Font& font;
	sf::RectangleShape shape;
	std::string buttonText;
public:
	Button(std::string identifier, sf::Font& font, std::string buttonText, sf::Vector2f size, sf::Color color);
	~Button();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	virtual void onClick();

	void update() override;
	void render(sf::RenderWindow& window) override;

	void setCharacterSize(const int size);
	void setPosition(const sf::Vector2f position);
};

