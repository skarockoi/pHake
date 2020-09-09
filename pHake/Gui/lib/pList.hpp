#ifndef _PLIST_HPP_
#define _PLIST_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "pItem.hpp"
#include "pButton.hpp"

class pList
{
private:
	bool active = false;
	bool used = false;

	sf::RenderWindow*  window;
	sf::Font		   font;
	sf::RectangleShape rect_back;

	std::vector<sf::Text>    items_name;
	std::vector<pItemBool>   items_bool;
	std::vector<pItemFloat>	 items_float;
	std::vector<pItemInt>	 items_int;
	std::vector<pItemString> items_string;
	std::vector<pButton>	 items_button;

	uint8_t count = 0;
	uint8_t gapCount = 0;

public:
	void create(sf::RenderWindow* const& window);
	void draw();
	void loop();
	void toggle();

	void addFloat(const std::string& name, float& value, float inc, float dec);
	void addFloat(const std::string& name, float& value, float inc, float dec, uint8_t prec);
	void addInt(const std::string& name, int& value, int inc, int dec);
	void addBool(const std::string& name, bool& value);
	void addFunction(const std::string& name, void(&functionP)());
	void addString(const std::string& name, std::string& value);
	void addGap();

public:
	bool isUsed();
	bool isActive();
	void setPosition(float x, float y);
	void setSize(float x, float y);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();

private:
	void addWord(const std::string& name);
	void setActive(bool act);
	void setUsed(bool act);
	void resize();
};
#endif