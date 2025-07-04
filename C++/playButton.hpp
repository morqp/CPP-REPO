#include "button.hpp"

class PlayButton : public Button {
private:
	SceneHandler& sceneHandler; // references scene handler to switch scenes
public:
	PlayButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler);
	void onClick() override;
};