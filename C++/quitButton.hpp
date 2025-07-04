#include "button.hpp"

class QuitButton : public Button {
private:
	sf::RenderWindow& window;
public:
	QuitButton(std::string identifier, sf::Font& font, sf::Vector2f size, sf::Color color, sf::RenderWindow& window);
	void onClick() override;
};