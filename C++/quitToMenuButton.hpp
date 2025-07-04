#include "button.hpp"

class QuitToMenuButton : public Button {
private:
	SceneHandler& sceneHandler;
public:
	QuitToMenuButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, SceneHandler& handler);
	void onClick() override;
};