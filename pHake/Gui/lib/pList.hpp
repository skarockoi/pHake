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

	sf::RenderWindow*  Window;
	sf::Font		   Font;
	sf::Vector2i	   Pos;
	sf::RectangleShape rectBack;

	std::vector<sf::Text>    itemName;
	std::vector<pItemBool>   itemBool;
	std::vector<pItemFloat>	 itemFloat;
	std::vector<pItemInt>	 itemInt;
	std::vector<pItemString> itemString;
	std::vector<pButton>	 itemButton;

	uint8_t count = 0;
	uint8_t gapCount = 0;

public:
	pList(){}

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
	void setPostion(int x, int y);
	void setSize(int x, int y);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();

private:
	void addWord(const std::string& name);
	void setActive(bool act);
	void setUsed(bool act);
	void resize();
};
#endif