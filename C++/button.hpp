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
	text.setCharacterSize(20);
	sf::FloatRect textBounds = text.getLocalBounds();
	sf::Vector2f centeredTextPos = position + sf::Vector2f((shape.getSize().x - textBounds.width) / 2.0f - textBounds.left, (shape.getSize().y - textBounds.height) / 2.0f - textBounds.top);
	text.setPosition(centeredTextPos);
}



class PlayButton : public Button {
private:
	SceneHandler& sceneHandler; // references scene handler to switch scenes
public:
	PlayButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler);
	void onClick() override;
};

PlayButton::PlayButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
	: Button(identifier, font, "Play", size, color), sceneHandler(handler) {}

void PlayButton::onClick() {
	printf("Play button clicked. Switching to stats scene.\n");
	sceneHandler.stackScene("statsScene");
}




class EraseDataButton : public Button {
private:
	SceneHandler& sceneHandler;  // references scene handler to reset high scores

public:
	EraseDataButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler);
	void onClick() override;
};

EraseDataButton::EraseDataButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
	: Button(identifier, font, "Erase Data", size, color), sceneHandler(handler) {}

void EraseDataButton::onClick() {
	printf("Erase Data Button Clicked. Resetting high scores.\n");
	sceneHandler.getHighscoreManager()->resetHighScoreList();
	sceneHandler.updateHighScoreText();
	std::cout << "High scores erased." << std::endl;
}



class QuitButton : public Button {
private:
	sf::RenderWindow& window;
public:
	QuitButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, sf::RenderWindow& window);
	void onClick() override;
};

QuitButton::QuitButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, sf::RenderWindow& window)
	: Button(identifier, font, "Quit", size, color), window(window) {}

void QuitButton::onClick() {
	this->window.close();
}



class QuitToMenuButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	QuitToMenuButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler);
	void onClick() override;
};

QuitToMenuButton::QuitToMenuButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
	: Button(identifier, font, "Quit to Menu", size, color), sceneHandler(handler) {}


void QuitToMenuButton::onClick() {
	// resets fight scene before switching to main menu
	Player* player = sceneHandler.getPlayer();
	Enemy* enemy = sceneHandler.getEnemy();

	if (player && enemy) {
		// resets player and enemy
		player->reset();
		enemy->reset();

		// updates output to player texts
		sceneHandler.updatePlayerHPText();
		sceneHandler.updateEnemyHPText();
		sceneHandler.setPlayerActionResultText("Player ready for battle.");
		sceneHandler.setEnemyActionResultText("Enemy ready for battle.");

		printf("Fight scene reset.\n");
	}

	if (sceneHandler.getCurrentScore() >= 1) {
		sceneHandler.getHighscoreManager()->addHighScore(sceneHandler.getCurrentScore());
		sceneHandler.updateHighScoreText();
	}
	sceneHandler.resetCurrentScore();
	sceneHandler.stackScene("mainMenuScene");
}



#pragma once

#include "button.hpp"
#include "sceneHandler.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class StatsButton : public Button {
private:
	SceneHandler& sceneHandler;
	std::string characterType;

public:
	StatsButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& sceneHandler, std::string characterType)
		: Button(identifier, font, characterType, size, color), sceneHandler(sceneHandler), characterType(characterType) {}

	void onClick() override {
		printf("Character selected: %s\n", characterType.c_str());

		Player* player = sceneHandler.getPlayer(); // accessing player through scene handler

		if (player != nullptr) {
			if (characterType == "Tank") {
				player->setMaxHealth(200);
				player->setHealth(200);
				player->setHealAmount(5);
				player->setAttackDamage(5);
			}
			else if (characterType == "Assassin") {
				player->setMaxHealth(75);
				player->setHealth(75);
				player->setHealAmount(5);
				player->setAttackDamage(20);
			}
			else if (characterType == "Mage") {
				player->setMaxHealth(100);
				player->setHealth(100);
				player->setHealAmount(15);
				player->setAttackDamage(5);
			}

			sceneHandler.updatePlayerHPText();

			printf("Player stats set - Health: %d, Heal Amount: %d, Attack Damage: %d\n",
				player->getHealth(), player->getHealAmount(), player->getAttackDamage());

			sceneHandler.stackScene("fightScene");

			printf("Switched to fight scene\n");
			Scene* currentScene = sceneHandler.getCurrentScene();
			if (currentScene) {
				printf("Current Scene after switch: %s\n", currentScene->getIdentifier().c_str());
			}
			else {
				printf("Error: Current Scene is null after switch\n");
			}
		}
		else {
			printf("Error: Player object is null.\n");
		}

	}
};



class AttackButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	AttackButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
		: Button(identifier, font, "Attack", size, color), sceneHandler(handler) {}

	void onClick() override {
		printf("Player attacks the enemy.\n");
		Player* player = sceneHandler.getPlayer();
		Enemy* enemy = sceneHandler.getEnemy();

		if (player && enemy) {
			enemy->takeDamage(player->getAttackDamage());
			sceneHandler.setPlayerActionResultText("Player attacked enemy for " + std::to_string(player->getAttackDamage()) + " damage.");
			sceneHandler.updateEnemyHPText();
			sceneHandler.setTurnState(TurnState::ENEMY_TURN);
		}
	}
};

class HealButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	HealButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
		: Button(identifier, font, "Heal", size, color), sceneHandler(handler) {}

	void onClick() override {
		printf("Player heals.\n");
		Player* player = sceneHandler.getPlayer();

		if (player) {
			int healAmount = player->getHealAmount();
			player->healAction();
			sceneHandler.setPlayerActionResultText("Player healed for " + std::to_string(healAmount) + ".");
			sceneHandler.updatePlayerHPText();
			sceneHandler.setTurnState(TurnState::ENEMY_TURN);
		}
	}
};

class DoNothingButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	DoNothingButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
		: Button(identifier, font, "Do Nothing", size, color), sceneHandler(handler) {}

	void onClick() override {
		printf("Player does nothing.\n");
		sceneHandler.setPlayerActionResultText("Player did nothing.");
		sceneHandler.setTurnState(TurnState::ENEMY_TURN);
	}
};
