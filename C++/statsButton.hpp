
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
		: Button(identifier, font, characterType, size, color), sceneHandler(sceneHandler), characterType(characterType) {
	}

	void onClick() override {
		printf("Character selected: %s\n", characterType.c_str());

		Player* player = sceneHandler.getPlayer(); // accessing player through scene handler

		if (player != nullptr) {
			if (characterType == "tank") {
				player->setMaxHealth(200);
				player->setHealth(200);
				player->setHealAmount(15);
				player->setAttackDamage(5);
			}
			else if (characterType == "damage") {
				player->setMaxHealth(60);
				player->setHealth(60);
				player->setHealAmount(10);
				player->setAttackDamage(20);
			}
			

			sceneHandler.updatePlayerHPText();

			printf("Player stats set - Health: %d, Heal Amount: %d, Attack Damage: %d\n",
				player->getHealth(), player->getHealAmount(), player->getAttackDamage());

			sceneHandler.updateTurnAndScoreText();
			
			printf("Turn and Score text reset");

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

