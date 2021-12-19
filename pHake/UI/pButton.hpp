#ifndef _PBUTTON_HPP_
#define _PBUTTON_HPP_

#include <SFML/Graphics.hpp>

class pButton
{
private:
	sf::RenderWindow   *window_;
	sf::Font		   *font_;

	sf::Text		   button_text_;
	sf::RectangleShape button_back_;

public:
	void Create(sf::RenderWindow* const& Window, sf::Font* font);
	void Connect(void(&function)());
	void Loop();
	void Draw();

public:
	void text(const std::string& text);
	void position(int x, int y);
	void size(int x, int y);
	sf::Vector2f size();

private:
	bool IsOnBox();
	void Hightlight(bool value);

private:
	uint16_t  sleep_duration_ = 150;
	bool	  active_ = false;
	bool	  busy_ = false;

	void* function_;
};
#endif