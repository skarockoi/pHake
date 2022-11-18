#ifndef _PLIST_HPP_
#define _PLIST_HPP_

#include <SFML/Graphics.hpp>
#include "pItem.hpp"
#include "pButton.hpp"

#include <vector>

class pList // stores and draws pItems, that is basically the menu
{
public:
	pList();
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
	void resize();

public:
	bool used();
	bool active();
	void position(sf::Vector2f xy);
	void size(sf::Vector2f xy);
	sf::Vector2f size();
	sf::Vector2f position();

private:
	sf::RenderWindow*  window_;
	sf::Font		   font_;
	sf::RectangleShape rect_back_;

	std::vector<sf::Text>    items_name_;
	std::vector<pItemBool>   items_bool_;
	std::vector<pItemFloat>	 items_float_;
	std::vector<pItemInt>	 items_int_;
	std::vector<pItemString> items_string_;
	std::vector<pButton>	 items_button_;

	uint8_t item_count_;
	uint8_t gap_count_;

	bool active_ = false;
	bool used_ = false;
};
#endif