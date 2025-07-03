#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "sceneHandler.hpp"
#include "scene.hpp"
#include "button.hpp"
#include "textObject.hpp"
#include "enemy.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Cosneanu 534295");
    sf::Font font;

    if (!font.loadFromFile("Namaku.ttf")) {
        return -1;
    }

    // scenes
    SceneHandler sceneHandler;
    Scene mainMenuScene("mainMenuScene");
    Scene statsScene("statsScene");
    Scene fightScene("fightScene");
    Scene gameOverScene("gameOverScene");


    // main menu
    
    //highscore
    TextObject highScoreText("highScoreText", font, "");
    highScoreText.setCharacterSize(20);
    highScoreText.setFillColor(sf::Color::Black);
    highScoreText.setPosition(sf::Vector2f(100.0f, 200.0f));
   
    std::vector<int> highScores = sceneHandler.getHighscoreManager()->getHighScoreList();
    std::string highScoreString = "High Scores:\n";
    for (int i = 0; i < highScores.size(); i++) {
        highScoreString += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
    }
    highScoreText.setText(highScoreString);

    //buttons
    PlayButton playButton("playButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler);
    playButton.setPosition(sf::Vector2f(540.0f, 250.0f));

    EraseDataButton eraseDataButton("eraseDataButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler);
    eraseDataButton.setPosition(sf::Vector2f(540.0f, 400.0f));

    QuitButton quitButton("quitButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Red, window);
    quitButton.setPosition(sf::Vector2f(540.0f, 550.0f));

    mainMenuScene.addGameObject(highScoreText);
    mainMenuScene.addGameObject(playButton);
    mainMenuScene.addGameObject(eraseDataButton);
    mainMenuScene.addGameObject(quitButton);


    // stats scene

    TextObject selectionSceneTitle("SelectionScreenTitle", font, "Select Your Stats");
    selectionSceneTitle.setCharacterSize(40);
    selectionSceneTitle.setFillColor(sf::Color::Black);
    selectionSceneTitle.setPosition(sf::Vector2f(450, 100));

    TextObject tankStats("tankStats", font, "HP: 200\nHealing: 5\nAttack: 5");
    tankStats.setCharacterSize(20);
    tankStats.setFillColor(sf::Color::Black);
    tankStats.setPosition(sf::Vector2f(250.0f, 300.0f));

    TextObject assassinStats("assassinStats", font, "HP: 75\nHealing: 5\nAttack: 20");
    assassinStats.setCharacterSize(20);
    assassinStats.setFillColor(sf::Color::Black);
    assassinStats.setPosition(sf::Vector2f(590.0f, 300.0f));

    TextObject mageStats("mageStats", font, "HP: 100\nHealing: 15\nAttack: 5");
    mageStats.setCharacterSize(20);
    mageStats.setFillColor(sf::Color::Black);
    mageStats.setPosition(sf::Vector2f(930.0f, 300.0f));

    //buttons
    StatsButton tankButton("tankButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler, "Tank");
    tankButton.setPosition(sf::Vector2f(200.0f, 400.0f));

    StatsButton assassinButton("assassinButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler, "Assassin");
    assassinButton.setPosition(sf::Vector2f(540.0f, 400.0f));

    StatsButton mageButton("mageButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler, "Mage");
    mageButton.setPosition(sf::Vector2f(880.0f, 400.0f));

    statsScene.addGameObject(selectionSceneTitle);
    statsScene.addGameObject(tankStats);
    statsScene.addGameObject(assassinStats);
    statsScene.addGameObject(mageStats);
    statsScene.addGameObject(tankButton);
    statsScene.addGameObject(assassinButton);
    statsScene.addGameObject(mageButton);


    // fight scene

    TextObject turnAndScoreCountText("turnCountText", font, "Turn:\nScore: ");
    turnAndScoreCountText.setCharacterSize(25);
    turnAndScoreCountText.setFillColor(sf::Color::Blue);
    turnAndScoreCountText.setPosition(sf::Vector2f(620.0f, 45.0f));

    //player
    Player player("player");
    player.setSpriteFile("player4.png");
    player.sprite->setPosition(sf::Vector2f(70.0f, 200.0f)); 

    TextObject playerHPText("playerHPText", font, "HP: " + std::to_string(player.getHealth()));
    playerHPText.setCharacterSize(20);
    playerHPText.setFillColor(sf::Color::Red);
    playerHPText.setPosition(sf::Vector2f(100.0f, 100.0f)); 

    TextObject playerActionResultText("playerActionResultText", font, "Player ready for battle!");
    playerActionResultText.setCharacterSize(15);
    playerActionResultText.setFillColor(sf::Color::Black);
    playerActionResultText.setPosition(sf::Vector2f(320.0f, 220.0f));

    //enemy
    Enemy enemy("enemy");
    enemy.setSpriteFile("enemy2.png");
    enemy.sprite->setPosition(sf::Vector2f(800.0f, 120.0f)); 
    enemy.setMaxHealth(100);
    enemy.setHealth(100);
    enemy.setAttackDamage(15);
    enemy.setHealAmount(10);

    TextObject enemyHPText("enemyHPText", font, "HP: " + std::to_string(enemy.getHealth()));
    enemyHPText.setCharacterSize(20);
    enemyHPText.setFillColor(sf::Color::Red);
    enemyHPText.setPosition(sf::Vector2f(1100.0f, 100.0f));

    TextObject enemyActionResultText("enemyActionResultText", font, "Enemy ready for battle!");
    enemyActionResultText.setCharacterSize(15);
    enemyActionResultText.setFillColor(sf::Color::Black);
    enemyActionResultText.setPosition(sf::Vector2f(700.0f, 480.0f));
    
    //buttons
    AttackButton attackButton("attackButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler);
    attackButton.setPosition(sf::Vector2f(300.0f, 550.0f));

    HealButton healButton("healButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler);
    healButton.setPosition(sf::Vector2f(540.0f, 550.0f));

    DoNothingButton doNothingButton("doNothingButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color(134, 134, 134), sceneHandler);
    doNothingButton.setPosition(sf::Vector2f(780.0f, 550.0f));

    QuitToMenuButton quitToMenuButton("quitToMenuButton", font, sf::Vector2f(150.0f, 40.0f), sf::Color::Red, sceneHandler);
    quitToMenuButton.setPosition(sf::Vector2f(540.0f, 650.0f));

    fightScene.addGameObject(turnAndScoreCountText);
    fightScene.addGameObject(playerActionResultText);
    fightScene.addGameObject(enemyActionResultText);
    fightScene.addGameObject(*player.sprite);  
    fightScene.addGameObject(*enemy.sprite);
    fightScene.addGameObject(playerHPText);
    fightScene.addGameObject(enemyHPText);
    fightScene.addGameObject(attackButton);
    fightScene.addGameObject(healButton);
    fightScene.addGameObject(doNothingButton);
    fightScene.addGameObject(quitToMenuButton);



    // gameover scene

    TextObject gameOverText("gameOverText", font, "GAME OVER!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(sf::Vector2f(480.0f, 200.0f));

    TextObject finalScoreText("finalScoreText", font, "");
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::Black);
    finalScoreText.setPosition(sf::Vector2f(520.0f, 300.0f));

    QuitToMenuButton gameOverQuitButton("gameOverQuitButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Red, sceneHandler);
    gameOverQuitButton.setPosition(sf::Vector2f(540.0f, 400.0f));

    gameOverScene.addGameObject(gameOverText);
    gameOverScene.addGameObject(finalScoreText);
    gameOverScene.addGameObject(gameOverQuitButton);


    // adding the scenes
    sceneHandler.addScene(mainMenuScene);
    sceneHandler.addScene(statsScene);
    sceneHandler.addScene(fightScene);
    sceneHandler.addScene(gameOverScene);


    while (window.isOpen()) {
        sf::Event event;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // handles events for all obj in a scene using public methods
                if (sceneHandler.scenesStackSize() > 0) {
                    Scene* currentScene = sceneHandler.getCurrentScene();
                    if (currentScene) {
                        for (auto& gameObject : currentScene->getGameObjects()) {
                            if (gameObject != nullptr) {
                                gameObject->handleEvent(event, window);
                            }
                            else {
                                printf("Warning: Null GameObject encountered while handling events.\n");
                            }
                        }
                    }
                    else {
                        printf("Error: Current Scene is null while polling events.\n");
                    }
                }
            }

            sceneHandler.update();
            window.clear(sf::Color::White);
            sceneHandler.render(window);
            window.display();
        }
    }

    return 0;
}