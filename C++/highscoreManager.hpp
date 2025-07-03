#include <fstream>
#include <sstream>
#include <string>
#include "gameObject.hpp"

class HighscoreManager : public GameObject {
    private:
        std::string fileName;
        std::vector<int> highscoreList;

    public:
        HighscoreManager(std::string identifier);
        ~HighscoreManager();

    public:
        void update() override;
        void render(sf::RenderWindow& window) override;

        void addHighScore(int score);
        std::vector<int> getHighScoreList(int max = 5) const;
        void resetHighScoreList();
        void updateHighScoreList();
};