#ifndef _PLIST_HPP_
#define _PLIST_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "pItem.hpp"
#include "pButton.hpp"

class pList
{
private:
	sf::RenderWindow* Window;
	sf::Font		   Font;
	sf::Vector2i	   Pos;
	sf::RectangleShape rectBack;

	std::vector<sf::Text> itemName;
	std::vector<pItemBool> itemBool;
	std::vector<pItemFloat> itemFloat;
	std::vector<pItemInt> itemInt;
	std::vector<pItemString> itemString;
	std::vector<pButton> itemButton;

	uint8_t count = 0;
	uint8_t gapCount = 0;

	bool active = false;
	bool used = false;

public:
	pList() {}

	void create(sf::RenderWindow* const& window)
	{
		Window = window;
		Font.loadFromFile("Settings/font.ttf");

		Pos.x = 0;
		Pos.y = 0;

		rectBack.setSize(sf::Vector2f(208, 0));
		rectBack.setPosition(Pos.x, Pos.y);
		rectBack.setFillColor(sf::Color::Color(0, 0, 0, 150));
		rectBack.setOutlineColor(sf::Color::Color(0, 0, 0));
		rectBack.setOutlineThickness(1);
	}


	void toggle()
	{
		active = not active;
	}

	void addFloat(const std::string &name, float& value, float inc, float dec)
	{
		pItemFloat tempFloat;
		tempFloat.create(Window);
		tempFloat.setFont(Font);
		tempFloat.addPtr(value, inc, dec);
		tempFloat.setFixedSize(48, 20);
		tempFloat.setPosition(rectBack.getSize().x - tempFloat.getSize().x + rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		tempFloat.setFillColor(sf::Color::Color(255, 255, 255, 255));
		itemFloat.push_back(tempFloat);

		this->addWord(name);
		this->resize();
	}

	void addFloat(const std::string& name, float& value, float inc, float dec, uint8_t prec)
	{
		pItemFloat tempFloat;
		tempFloat.create(Window);
		tempFloat.setFont(Font);
		tempFloat.addPtr(value, inc, dec);
		tempFloat.setPrecision(prec);
		tempFloat.setFixedSize(48, 20);
		tempFloat.setPosition(rectBack.getSize().x - tempFloat.getSize().x + rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		tempFloat.setFillColor(sf::Color::Color(255, 255, 255, 255));
		itemFloat.push_back(tempFloat);

		this->addWord(name);
		this->resize();
	}

	void addInt(const std::string& name, int& value, int inc, int dec)
	{
		pItemInt tempInt;
		tempInt.create(Window);
		tempInt.setFont(Font);
		tempInt.addPtr(value, inc, dec);
		tempInt.setFixedSize(48, 20);
		tempInt.setPosition(rectBack.getSize().x - tempInt.getSize().x + rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		tempInt.setFillColor(sf::Color::Color(255, 255, 255, 255));
		itemInt.push_back(tempInt);

		this->addWord(name);
		this->resize();
	}

	void addBool(const std::string& name, bool& value)
	{
		pItemBool tempBool;
		tempBool.create(Window);
		tempBool.setFont(Font);
		tempBool.addPtr(value, 1, 1);
		tempBool.setFixedSize(48, 20);
		tempBool.setPosition(rectBack.getSize().x - tempBool.getSize().x + rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		tempBool.setFillColor(sf::Color::Color(255, 255, 255, 255));
		itemBool.push_back(tempBool);

		this->addWord(name);
		this->resize();
	}


	void addFunction(const std::string& name, void(&functionP)())
	{
		pButton tempButton;
		tempButton.create(Window);
		tempButton.setFont(Font);
		tempButton.connect(functionP);
		tempButton.setFixedSize(48, 19);
		tempButton.setPosition(rectBack.getSize().x - tempButton.getSize().x + rectBack.getPosition().x , rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		itemButton.push_back(tempButton);

		this->addWord(name);
		this->resize();
	}

	void addString(const std::string& name, std::string& value)
	{
		pItemString tempString;
		tempString.create(Window);
		tempString.setFont(Font);
		tempString.addPtr(value);
		tempString.setFixedSize(48, 20);
		tempString.setPosition(rectBack.getSize().x - tempString.getSize().x + rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		itemString.push_back(tempString);

		this->addWord(name);
		this->resize();
	}

	void addGap()
	{
		gapCount++;
	}

	void loop()
	{
		if (this->isActive() && this->isUsed())
		{
			for (int i = 0; i < itemBool.size(); i++)
				itemBool[i].loop();

			for (int i = 0; i < itemFloat.size(); i++)
				itemFloat[i].loop();

			for (int i = 0; i < itemInt.size(); i++)
				itemInt[i].loop();

			for (int i = 0; i < itemButton.size(); i++)
				itemButton[i].Loop();

			for (int i = 0; i < itemString.size(); i++)
				itemString[i].loop();
		}
	}

	void draw()
	{
		if (this->isActive() && this->isUsed())
		{
			Window->draw(rectBack);

			for (int i = 0; i < itemName.size(); i++)
				Window->draw(itemName[i]);

			for (int i = 0; i < itemBool.size(); i++)
				itemBool[i].draw();
					
			for (int i = 0; i < itemFloat.size(); i++)
				itemFloat[i].draw();

			for (int i = 0; i < itemInt.size(); i++)
				itemInt[i].draw();

			for (int i = 0; i < itemButton.size(); i++)
				itemButton[i].draw();

			for (int i = 0; i < itemString.size(); i++)
				itemString[i].draw();
		}
	}

	void setPostion(int x, int y)
	{
		rectBack.setPosition(x, y);
	}

	void setSize(int x, int y)
	{
		rectBack.setSize(sf::Vector2f(x, y));
	}

	sf::Vector2f getSize()
	{
		return rectBack.getSize();
	}

	sf::Vector2f getPosition()
	{
		return rectBack.getPosition();
	}

	bool isUsed()
	{
		return this->used;
	}

	bool isActive()
	{
		return this->active;
	}

private:
	void addWord(const std::string& name)
	{
		if (!this->isUsed())
			setUsed(true);
		
		sf::Text tempWord;
		tempWord.setFont(Font);
		tempWord.setCharacterSize(16);
		tempWord.setFillColor(sf::Color::Color(255, 255, 255, 255));
		tempWord.setPosition(rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
		tempWord.setString(name);
		itemName.push_back(tempWord);
		count++;
	}

	void setActive(bool act)
	{
		active = act;
	}

	void setUsed(bool act)
	{
		used = act;
	}
	void resize()
	{
		rectBack.setSize(sf::Vector2f(rectBack.getSize().x, (itemName.size() * 20) + (gapCount * 5)));
	}
};
#endif