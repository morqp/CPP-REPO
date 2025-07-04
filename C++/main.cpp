#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "sceneHandler.hpp"
#include "scene.hpp"
#include "textObject.hpp"
#include "enemy.hpp"
#include "button.hpp"
#include "playButton.hpp"
#include "eraseDataButton.hpp"
#include "quitButton.hpp"
#include "statsButton.hpp"
#include "attackButton.hpp"
#include "healButton.hpp"
#include "doNothingButton.hpp"
#include "quitToMenuButton.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Maria Cosneanu 534295");
    sf::Font font;

    if (!font.loadFromFile("Robot Crush.ttf")) {
        return -1;
    }

    // scenes
    SceneHandler sceneHandler;
    Scene mainMenuScene("mainMenuScene");
    Scene statsScene("statsScene");
    Scene fightScene("fightScene");
    Scene gameOverScene("gameOverScene");


    // main menu

    //title
    TextObject title("title", font, "FIGHTER GAME");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(400.0f, 100.0f));
    
    //highscore
    TextObject highScoreText("highScoreText", font, "");
    highScoreText.setCharacterSize(20);
    highScoreText.setFillColor(sf::Color::Black);
    highScoreText.setPosition(sf::Vector2f(580.0f, 470.0f));
   
    std::vector<int> highScores = sceneHandler.getHighscoreManager()->getHighScoreList();
    std::string highScoreString = "High Scores:\n";
    for (int i = 0; i < highScores.size(); i++) {
        highScoreString += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
    }
    highScoreText.setText(highScoreString);

    //buttons
    PlayButton playButton("playButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler);
    playButton.setPosition(sf::Vector2f(540.0f, 300.0f));

    EraseDataButton eraseDataButton("eraseDataButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler);
    eraseDataButton.setPosition(sf::Vector2f(540.0f, 400.0f));

    QuitButton quitButton("quitButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Red, window);
    quitButton.setPosition(sf::Vector2f(540.0f, 600.0f));

    mainMenuScene.addGameObject(title);
    mainMenuScene.addGameObject(highScoreText);
    mainMenuScene.addGameObject(playButton);
    mainMenuScene.addGameObject(eraseDataButton);
    mainMenuScene.addGameObject(quitButton);


    // stats scene

    TextObject selectionSceneTitle("SelectionScreenTitle", font, "Select Your Stats");
    selectionSceneTitle.setCharacterSize(50);
    selectionSceneTitle.setFillColor(sf::Color::Black);
    selectionSceneTitle.setPosition(sf::Vector2f(450, 120));

    TextObject tankStats("tankStats", font, "HP: 200\nhealing: 15\nattack: 5");
    tankStats.setCharacterSize(30);
    tankStats.setFillColor(sf::Color::Black);
    tankStats.setPosition(sf::Vector2f(320.0f, 350.0f));

    TextObject assassinStats("assassinStats", font, "HP: 60\nhealing: 10\nattack: 20");
    assassinStats.setCharacterSize(30);
    assassinStats.setFillColor(sf::Color::Black);
    assassinStats.setPosition(sf::Vector2f(770.0f, 350.0f));


    //buttons
    StatsButton tankButton("tankButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler, "tank");
    tankButton.setPosition(sf::Vector2f(300.0f, 300.0f));

    StatsButton assassinButton("damageButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler, "damage");
    assassinButton.setPosition(sf::Vector2f(750.0f, 300.0f));


    statsScene.addGameObject(selectionSceneTitle);
    statsScene.addGameObject(tankStats);
    statsScene.addGameObject(assassinStats);
    statsScene.addGameObject(tankButton);
    statsScene.addGameObject(assassinButton);


    // fight scene

    TextObject turnAndScoreCountText("turnCountText", font, "turn:\nscore: ");
    turnAndScoreCountText.setCharacterSize(50);
    turnAndScoreCountText.setFillColor(sf::Color::Black);
    turnAndScoreCountText.setPosition(sf::Vector2f(550.0f, 50.0f));

    //player
    Player player("player");
    player.setSpriteFile("player4.png");
    player.sprite->setPosition(sf::Vector2f(70.0f, 200.0f)); 

    TextObject playerHPText("playerHPText", font, "hp: " + std::to_string(player.getHealth()));
    playerHPText.setCharacterSize(30);
    playerHPText.setFillColor(sf::Color::Green);
    playerHPText.setPosition(sf::Vector2f(100.0f, 150.0f)); 

    TextObject playerActionResultText("playerActionResultText", font, "player ready for battle!");
    playerActionResultText.setCharacterSize(25);
    playerActionResultText.setFillColor(sf::Color::Black);
    playerActionResultText.setPosition(sf::Vector2f(320.0f, 220.0f));

    //enemy
    Enemy enemy("enemy");
    enemy.setSpriteFile("enemy2.png");
    enemy.sprite->setPosition(sf::Vector2f(800.0f, 150.0f)); 
    enemy.setMaxHealth(100);
    enemy.setHealth(100);
    enemy.setAttackDamage(15);
    enemy.setHealAmount(10);

    TextObject enemyHPText("enemyHPText", font, "HP: " + std::to_string(enemy.getHealth()));
    enemyHPText.setCharacterSize(30);
    enemyHPText.setFillColor(sf::Color::Red);
    enemyHPText.setPosition(sf::Vector2f(1100.0f, 150.0f));

    TextObject enemyActionResultText("enemyActionResultText", font, "enemy ready for battle!");
    enemyActionResultText.setCharacterSize(25);
    enemyActionResultText.setFillColor(sf::Color::Black);
    enemyActionResultText.setPosition(sf::Vector2f(680.0f, 490.0f));
    
    //buttons
    AttackButton attackButton("attackButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler);
    attackButton.setPosition(sf::Vector2f(300.0f, 550.0f));

    HealButton healButton("healButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler);
    healButton.setPosition(sf::Vector2f(540.0f, 550.0f));

    DoNothingButton doNothingButton("doNothingButton", font, sf::Vector2f(200.0f, 50.0f), sf::Color::Black, sceneHandler);
    doNothingButton.setPosition(sf::Vector2f(780.0f, 550.0f));

    QuitToMenuButton quitToMenuButton("quitToMenuButton", font, sf::Vector2f(180.0f, 40.0f), sf::Color::Red, sceneHandler);
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
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(sf::Vector2f(450.0f, 200.0f));

    TextObject finalScoreText("finalScoreText", font, "");
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::Black);
    finalScoreText.setPosition(sf::Vector2f(540.0f, 300.0f));

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