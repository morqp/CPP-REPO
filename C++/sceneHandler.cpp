#include "sceneHandler.hpp"
#include "textObject.hpp"
#include "scene.hpp"
#include <thread>
#include <chrono>
class Player; // declaring forward


SceneHandler::SceneHandler() : player("player"), enemy("enemy"), highscoreManager("highscoreManager")
{
    currentScore = 0;
    turnCount = 0;
}

SceneHandler::~SceneHandler() { }

void SceneHandler::render(sf::RenderWindow& window) const {
    if (this->scenesStack.size() != 0) {
        this->scenesStack.top()->render(window);
    }
}

void SceneHandler::update() {
    if (this->scenesStack.size() != 0) {
        this->scenesStack.top()->update();
    }
}

void SceneHandler::addScene(Scene& scene) {
    this->scenes.emplace(scene.getIdentifier(), &scene);
    if (this->scenes.size() == 1) {
        this->stackScene(scene.getIdentifier());
    }
}

void SceneHandler::stackScene(std::string sceneName) {
    auto sceneIter = scenes.find(sceneName);
    if (sceneIter != scenes.end()) {
        this->scenesStack.push(sceneIter->second);
        printf("Scene '%s' successfully pushed to stack.\n", sceneName.c_str());
    }
    else {
        printf("Error: Scene '%s' not found!\n", sceneName.c_str());
    }
}


void SceneHandler::updatePlayerHPText() {
    Player* player = getPlayer(); // accessing player through scene handler
    if (player) {
        if (Scene* fightScene = scenes["fightScene"]) {
            for (auto& gameObject : fightScene->getGameObjects()) {
                if (TextObject* hpText = dynamic_cast<TextObject*>(gameObject)) {
                    if (hpText->getIdentifier() == "playerHPText") {
                        hpText->setText("HP: " + std::to_string(player->getHealth()));
                    }
                }
            }
        }
    }
}


void SceneHandler::updateEnemyHPText() {
    Enemy* enemy = getEnemy(); // accessing player through scene handler
    if (enemy) {
        if (Scene* fightScene = scenes["fightScene"]) {
            for (auto& gameObject : fightScene->getGameObjects()) {
                if (TextObject* hpText = dynamic_cast<TextObject*>(gameObject)) {
                    if (hpText->getIdentifier() == "enemyHPText") {
                        hpText->setText("HP: " + std::to_string(enemy->getHealth()));
                    }
                }
            }
        }
    }
}

void SceneHandler::updateTurnAndScoreText() {
    if (Scene* fightScene = scenes["fightScene"]) {
        for (auto& gameObject : fightScene->getGameObjects()) {
            if (TextObject* turnScoreText = dynamic_cast<TextObject*>(gameObject)) {
                if (turnScoreText->getIdentifier() == "turnCountText") {
                    turnScoreText->setText("Turn: " + std::to_string(turnCount) + "\nScore: " + std::to_string(currentScore));
                }
            }
        }
    }
}


void SceneHandler::setPlayerActionResultText(const std::string& text) {
    if (Scene* fightScene = scenes["fightScene"]) {
        for (auto& gameObject : fightScene->getGameObjects()) {
            if (TextObject* resultText = dynamic_cast<TextObject*>(gameObject)) {
                if (resultText->getIdentifier() == "playerActionResultText") {
                    resultText->setText(text);
                }
            }
        }
    }
}

void SceneHandler::setEnemyActionResultText(const std::string& text) {
    if (Scene* fightScene = scenes["fightScene"]) {
        for (auto& gameObject : fightScene->getGameObjects()) {
            if (TextObject* resultText = dynamic_cast<TextObject*>(gameObject)) {
                if (resultText->getIdentifier() == "enemyActionResultText") {
                    resultText->setText(text);
                }
            }
        }
    }
}


void SceneHandler::popScene(void) {
    this->scenesStack.pop();
}


TurnState SceneHandler::getCurrentTurnState() const {
    return currentTurnState;
}


void SceneHandler::enemyTurn() {
    printf("Entering enemyTurn(), currentTurnState: %d\n", static_cast<int>(currentTurnState));

    if (currentTurnState == TurnState::ENEMY_TURN) {
        printf("Enemy's turn is starting.\n");
        Enemy* enemy = getEnemy();
        Player* player = getPlayer();

        if (enemy && player) {
            int action = enemy->chooseAction();
            printf("Enemy action chosen: %d\n", action);

            if (action == 0) { // attack action
                player->takeDamage(enemy->getAttackDamage());
                printf("Enemy attacks for %d damage\n", enemy->getAttackDamage());
                setEnemyActionResultText("Enemy attacked player for " + std::to_string(enemy->getAttackDamage()) + " damage.");
                updatePlayerHPText();
            }
            else if (action == 1) { // heal action
                printf("Calling healAction()\n");
                enemy->healAction();
                printf("After calling healAction()\n");
                setEnemyActionResultText("Enemy healed for " + std::to_string(enemy->getHealAmount()) + ".");
                updateEnemyHPText();
            }
            else if (action == 2) { // do nothing action
                printf("Enemy does nothing\n");
                setEnemyActionResultText("Enemy did nothing.");
            }
            else if (action == 4) // enemy died
            {
                updateEnemyHPText();
                setEnemyActionResultText("Enemy slain, spawning new one!");
                setPlayerActionResultText("");
                player->reset();
                updatePlayerHPText();
                currentScore++;
                turnCount = 0;

            }

            if (player->getHealth() <= 0) {
                handlePlayerDeath();
            }
            else {
                setTurnState(TurnState::PLAYER_TURN);
            }
        }

        printf("Exiting enemyTurn()\n\n\n");
    }
}




void SceneHandler::setTurnState(TurnState state) {
    currentTurnState = state;

    if (currentTurnState == TurnState::ENEMY_TURN) {
        enemyTurn();
    }
    else if (currentTurnState == TurnState::PLAYER_TURN) {
        turnCount++;
        updateTurnAndScoreText(); 
    }
}

void SceneHandler::resetCurrentScore() {
    currentScore = 0;
}

int SceneHandler::getCurrentScore() const {
    return currentScore;
}

void SceneHandler::handlePlayerDeath() {
    printf("Player has died. Saving high score: %d\n", currentScore);
    if (currentScore >= 1) {
        highscoreManager.addHighScore(currentScore);
    }

    Scene* gameOverScene = scenes["gameOverScene"];
    if (gameOverScene) {
        for (auto& gameObject : gameOverScene->getGameObjects()) {
            if (TextObject* finalScoreText = dynamic_cast<TextObject*>(gameObject)) {
                if (finalScoreText->getIdentifier() == "finalScoreText") {
                    finalScoreText->setText("Final Score: " + std::to_string(currentScore));
                }
            }
        }
    }
    resetCurrentScore();
    turnCount = 0;

    // update high score on main menu
    Scene* mainMenuScene = scenes["mainMenuScene"];
    if (mainMenuScene) {
        for (auto& gameObject : mainMenuScene->getGameObjects()) {
            if (TextObject* scoreText = dynamic_cast<TextObject*>(gameObject)) {
                if (scoreText->getIdentifier() == "highScoreText") {
                    std::vector<int> highScores = highscoreManager.getHighScoreList();
                    std::string highScoreString = "High Scores:\n";
                    for (int i = 0; i < highScores.size(); i++) {
                        highScoreString += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
                    }
                    scoreText->setText(highScoreString);
                }
            }
        }
    }

    setEnemyActionResultText("Player has died. High score saved.");
    stackScene("gameOverScene");  // return player to main menu
}

void SceneHandler::updateHighScoreText() {
    Scene* mainMenuScene = scenes["mainMenuScene"];
    if (mainMenuScene) {
        for (auto& gameObject : mainMenuScene->getGameObjects()) {
            if (TextObject* scoreText = dynamic_cast<TextObject*>(gameObject)) {
                if (scoreText->getIdentifier() == "highScoreText") {
                    std::vector<int> highScores = highscoreManager.getHighScoreList();
                    std::string highScoreString = "High Scores:\n";
                    for (int i = 0; i < highScores.size(); i++) {
                        highScoreString += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
                    }
                    scoreText->setText(highScoreString);
                }
            }
        }
    }
}




Scene* SceneHandler::getCurrentScene() const {
    if (!scenesStack.empty()) {
        return this->scenesStack.top();
    }
    return nullptr;
}

int SceneHandler::scenesStackSize() const {
    return static_cast<int>(this->scenesStack.size());
}

Player* SceneHandler::getPlayer() {
    return &player;
}

Enemy* SceneHandler::getEnemy()
{
    return &enemy;
}



