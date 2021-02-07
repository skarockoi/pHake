#ifndef _PLIST_HPP_
#define _PLIST_HPP_

#include "pItem.hpp"
#include "pButton.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class pList
{
private:
	bool active_ = false;
	bool used_ = false;

	sf::RenderWindow*  window_;
	sf::Font		   font_;
	sf::RectangleShape rect_back;

	std::vector<sf::Text>    items_name_;
	std::vector<pItemBool>   items_bool_;
	std::vector<pItemFloat>	 items_float_;
	std::vector<pItemInt>	 items_int_;
	std::vector<pItemString> items_string_;
	std::vector<pButton>	 items_button_;

	uint8_t item_count_ = 0;
	uint8_t gap_count_ = 0;

public:
	void Create(sf::RenderWindow* const& window);
	void Draw();
	void Loop();
	void Toggle();

	void AddFloat(const std::string& name, float& value, float inc, float dec);
	void AddInt(const std::string& name, uint32_t& value, int inc, int dec);
	void AddBool(const std::string& name, bool& value);
	void AddFunction(const std::string& name, void(&functionP)());
	void AddString(const std::string& name, std::string& value);
	void AddGap();
private:
	void AddWord(const std::string& name);

public:
	bool used();
	bool active();
	void position(float x, float y);
	void size(float x, float y);
	sf::Vector2f size();
	sf::Vector2f position();

private:
	void used(bool act);
	void active(bool act);
	void resize();
};
#endif