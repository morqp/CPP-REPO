#include "playButton.hpp"

PlayButton::PlayButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
	: Button(identifier, font, "Play", size, color), sceneHandler(handler) {
}

void PlayButton::onClick() {
	printf("Play button clicked. Switching to stats scene.\n");
	sceneHandler.stackScene("statsScene");
}