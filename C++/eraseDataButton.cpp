#include "eraseDataButton.hpp"


EraseDataButton::EraseDataButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
	: Button(identifier, font, "Erase Data", size, color), sceneHandler(handler) {
}

void EraseDataButton::onClick() {
	printf("Erase Data Button Clicked. Resetting high scores.\n");
	sceneHandler.getHighscoreManager()->resetHighScoreList();
	sceneHandler.updateHighScoreText();
	std::cout << "High scores erased." << std::endl;
}