#ifndef _PBUTTON_HPP_
#define _PBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <functional>

class pButton // rectangle button that executes a function when pressed
{
public:
	pButton();
	void Create(sf::RenderWindow* const& Window, sf::Font* font);

	void Connect(std::function<void()> function);

	void Draw();
	void Loop();

public:
	void text(const std::string& text);
	void position(float x, float y);
	void size(float x, float y);
	sf::Vector2f size();

private:
	bool IsOnBox();
	void Hightlight(bool value);

private:
	sf::RenderWindow* window_;
	sf::Font*		  font_;

	sf::Text		   button_text_;
	sf::RectangleShape button_back_;

private:
	std::function<void()> function_;
	bool	  active_;
	bool	  busy_;
	uint16_t  sleep_duration_;
};
#endif
