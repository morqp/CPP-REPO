#include "button.hpp"

class EraseDataButton : public Button {
private:
	SceneHandler& sceneHandler;  // references scene handler to reset high scores

public:
	EraseDataButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler);
	void onClick() override;
};