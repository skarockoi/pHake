#ifndef _PBUTTON_HPP_
#define _PBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <future>

class pButton
{
protected:
	uint16_t  sleep_time_ = 150;
	bool	  resize_ = true;
	bool	  active_ = false;
	bool	  busy_ = false;

	void*	  function_;

	sf::RenderWindow   *window_;
	sf::Font		   font_;

	sf::Text		   button_text_;
	sf::RectangleShape button_back_;

public:
	void Create(sf::RenderWindow* const& window);
	void Connect(void(&functionP)());
	void Loop();
	void Draw();

public:
	bool active();
	void text(const std::string& text);
	void position(int x, int y);
	void timeout(int sleep);
	void fixed_size(int x, int y);
	void font(sf::Font& font);
	sf::Vector2f size();

protected:
	bool IsOnBox();
	void active(bool act);
	void highlight(bool value);
	void update_length();
};
#endif