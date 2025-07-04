#pragma once

#include "button.hpp"
#include "sceneHandler.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class DoNothingButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	DoNothingButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
		: Button(identifier, font, "Do Nothing", size, color), sceneHandler(handler) {
	}

	void onClick() override {
		printf("Player does nothing.\n");
		sceneHandler.setPlayerActionResultText("Player did nothing.");
		sceneHandler.setTurnState(TurnState::ENEMY_TURN);
	}
};