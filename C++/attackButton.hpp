#pragma once

#include "button.hpp"
#include "sceneHandler.hpp"
#include <SFML/Graphics.hpp>
#include <string>


class AttackButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	AttackButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
		: Button(identifier, font, "Attack", size, color), sceneHandler(handler) {
	}

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