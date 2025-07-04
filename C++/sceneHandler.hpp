#pragma once

#include <map>
#include <stack>
#include "scene.hpp"
#include "player.hpp"
#include "enemy.hpp"    
#include "highscoreManager.hpp"

enum class TurnState {
    PLAYER_TURN,
    ENEMY_TURN
};

class SceneHandler {
    private:
        std::map<std::string, Scene*> scenes;
        std::stack<Scene*> scenesStack;
        Player player;
        Enemy enemy;
        TurnState currentTurnState = TurnState::PLAYER_TURN; 
        HighscoreManager highscoreManager;
        int currentScore;
        int turnCount;
    public:
        SceneHandler(); 
        ~SceneHandler();

        void render(sf::RenderWindow& window) const;
        void update();

        void addScene(Scene& scene);
        void stackScene(std::string sceneName);
        void popScene();
        Scene* getCurrentScene() const;
        int scenesStackSize() const;

        TurnState getCurrentTurnState() const;
        void setTurnState(TurnState state);

        void setPlayerActionResultText(const std::string& text);
        void setEnemyActionResultText(const std::string& text);
        void updatePlayerHPText();
        void updateEnemyHPText();
        void updateTurnAndScoreText();
        void enemyTurn();
        void handlePlayerDeath();

        HighscoreManager* getHighscoreManager() {
            return &highscoreManager;
        }
        void updateHighScoreText();
        int getCurrentScore() const;
        void resetCurrentScore();
        void resetCurrentTurn();

        Player* getPlayer();
        Enemy* getEnemy();
};