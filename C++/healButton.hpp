#pragma once

#include "button.hpp"
#include "sceneHandler.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class HealButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	HealButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
		: Button(identifier, font, "Heal", size, color), sceneHandler(handler) {
	}

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