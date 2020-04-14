#ifndef _PBUTTON_HPP_
#define _PBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <future>

class pButton
{
protected:
	uint16_t  sleep_time = 150;
	bool	  resize = true;
	bool	  active = false;
	bool	  busy = false;

	void*	  function;

	sf::RenderWindow   *window;
	sf::Font		   font;

	sf::Text		   button_text;
	sf::RectangleShape button_back;

public:
	void create(sf::RenderWindow* const& window);
	void connect(void(&functionP)());
	void loop();
	void draw();

public:
	bool isActive();
	void setText(const std::string& text);
	void setPosition(int x, int y);
	void setTimeout(int sleep);
	void setFixedSize(int x, int y);
	void setFont(sf::Font& font);
	sf::Vector2f getSize();

protected:
	bool isOnBox();
	void execFunction();
	void setActive(bool act);
	void setHighlight(bool value);
	void updateLength();
};
#endif