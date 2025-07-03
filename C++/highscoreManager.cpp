#include "highscoreManager.hpp"

HighscoreManager::HighscoreManager(std::string identifier) : GameObject(identifier) {
	this->highscoreList = getHighScoreList();
}

HighscoreManager::~HighscoreManager() {
}

void HighscoreManager::update() {
}

void HighscoreManager::render(sf::RenderWindow& window) {
}

void HighscoreManager::addHighScore(int score) {
	std::vector<int> highscoreList = getHighScoreList();
	highscoreList.push_back(score);
	std::string fileName = "typed.cmgt";
	std::sort(highscoreList.begin(), highscoreList.end(), std::greater<int>());
	std::ofstream file(fileName);

	for (int i = 0; i < highscoreList.size(); i++) {
		file << std::to_string(highscoreList[i]) << std::endl;
	}

	file.close();
}


std::vector<int> HighscoreManager::getHighScoreList(int max) const {
	std::vector<int> highscoreList;
	highscoreList.reserve(max);
	std::string fileName = "typed.cmgt";
	std::ifstream file(fileName);
	std::string line;

	if (!file) {
		file.close();

		std::ofstream newFile(fileName);
		newFile.close();
	}
	else {

		while (std::getline(file, line)) {
			highscoreList.push_back(std::stoi(line));
		}

		file.close();
	}

	std::sort(highscoreList.begin(), highscoreList.end(), std::greater<int>());

	printf("Highscore list: %zu \n", highscoreList.size());

	if (highscoreList.size() > max) {
		highscoreList.resize(max);
	}

	return highscoreList;
}

void HighscoreManager::resetHighScoreList() {
	std::string fileName = "typed.cmgt";
	std::ofstream file(fileName, std::ios::trunc);
	file.close();
}

void HighscoreManager::updateHighScoreList() {
	highscoreList = getHighScoreList();
}