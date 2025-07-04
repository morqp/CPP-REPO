#include "quitToMenuButton.hpp"


QuitToMenuButton::QuitToMenuButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler)
	: Button(identifier, font, "Quit to Menu", size, color), sceneHandler(handler) {
}


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
		sceneHandler.resetCurrentScore();
		sceneHandler.resetCurrentTurn();

		printf("Fight scene reset.\n");
	}

	if (sceneHandler.getCurrentScore() >= 1) {
		sceneHandler.getHighscoreManager()->addHighScore(sceneHandler.getCurrentScore());
		sceneHandler.updateHighScoreText();
	}
	sceneHandler.resetCurrentScore();
	sceneHandler.stackScene("mainMenuScene");
}
