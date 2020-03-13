#ifndef _PLISTVIEW_HPP_
#define _PLISTVIEW_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include "pItem.hpp"
#include "pButton.hpp"

class pList
{
private:
	sf::RenderWindow   *Window;
	sf::Font		   Font;
	sf::Vector2i	   Pos;
	sf::RectangleShape rMain;

	sf::Text wWord[32];
	sf::Text wItems[32];
	pItem<bool> bItems[32];
	pItem<float> fItems[32];
	pItem<int> iItems[32];
	pButton btItems[32];
	
	uint8_t sCount = 0;
	uint8_t bCount = 0;
	uint8_t fCount = 0;
	uint8_t iCount = 0;
	uint8_t btCount = 0;
	uint8_t count = 0;

	bool active = false;


public:
	pList() {}

	void create(sf::RenderWindow* const& window)
	{
		setActive(1);

		Window = window;
		Font.loadFromFile("Settings/font.ttf");

		Pos.x = 0;
		Pos.y = 0;

		rMain.setSize(sf::Vector2f(210, 150));
		rMain.setPosition(Pos.x, Pos.y);
		rMain.setFillColor(sf::Color::Color(0, 0, 0, 150));
		rMain.setOutlineColor(sf::Color::Color(0, 0, 0));
		rMain.setOutlineThickness(1);
	}


	void toggle()
	{
		active = not active;
	}

	void addFloat(std::string name, float& value, float inc, float dec)
	{
		wWord[count].setFont(Font);
		wWord[count].setCharacterSize(16);
		wWord[count].setFillColor(sf::Color::Color(255, 255, 255, 255));
		wWord[count].setPosition(rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		wWord[count].setString(name);

		fItems[fCount].create(Window);
		fItems[fCount].addPtr(value, inc, dec);
		fItems[fCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		fItems[fCount].setFixedSize(48, 20);
		fItems[fCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		fCount++;
		count++;
		this->resize();
	}

	void addInt(std::string name, int& value, int inc, int dec)
	{
		wWord[count].setFont(Font);
		wWord[count].setCharacterSize(16);
		wWord[count].setFillColor(sf::Color::Color(255, 255, 255, 255));
		wWord[count].setPosition(rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		wWord[count].setString(name);

		iItems[iCount].create(Window);
		iItems[iCount].addPtr(value, inc, dec);
		iItems[iCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		iItems[iCount].setFixedSize(48, 20);
		iItems[iCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		iCount++;
		count++;
		this->resize();
	}

	void addBool(std::string name, bool& value)
	{
		wWord[count].setFont(Font);
		wWord[count].setCharacterSize(16);
		wWord[count].setFillColor(sf::Color::Color(255, 255, 255, 255));
		wWord[count].setPosition(rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		wWord[count].setString(name);

		bItems[bCount].create(Window);
		bItems[bCount].addPtr(value, 1, 1);
		bItems[bCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		bItems[bCount].setFixedSize(48, 20);
		bItems[bCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		bCount++;
		count++;
		this->resize();
	}


	void addFunction(std::string name, void(&functionP)())
	{
		wWord[count].setFont(Font);
		wWord[count].setCharacterSize(16);
		wWord[count].setFillColor(sf::Color::Color(255, 255, 255, 255));
		wWord[count].setPosition(rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		wWord[count].setString(name);bItems[bCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		btItems[btCount].create(Window);
		btItems[btCount].connect(functionP);
		btItems[btCount].setPostion(160 + rMain.getPosition().x - 1, rMain.getPosition().y + (count * 20));
		btItems[btCount].setFixedSize(50, 19);
		
		btCount++;
		count++;
		this->resize();
	}

	void addString(std::string name)
	{
		wWord[count].setFont(Font);
		wWord[count].setCharacterSize(16);
		wWord[count].setFillColor(sf::Color::Color(255, 255, 255, 255));
		wWord[count].setPosition(rMain.getPosition().x, rMain.getPosition().y + (count * 20));
		wWord[count].setString(name); bItems[bCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		sCount++;
		count++;
		this->resize();
	}


	void setPostion(int x, int y)
	{
		rMain.setPosition(x, y);
	}

	void Loop()
	{
		if (this->isActive())
		{
			for (int i = 0; i < 32; i++)
				bItems[i].Loop();

			for (int i = 0; i < 32; i++)
				fItems[i].Loop();

			for (int i = 0; i < 32; i++)
				iItems[i].Loop();

			for (int i = 0; i < 32; i++)
				btItems[i].Loop();
		}
	}

	void draw()
	{
		if (isActive())
		{
			Window->draw(rMain);

			for (int i = 0; i < 32; i++)
				Window->draw(wItems[i]);

			for (int i = 0; i < 32; i++)
				Window->draw(wWord[i]);

			for (int i = 0; i < 32; i++)		
				bItems[i].draw();
			
			for (int i = 0; i < 32; i++)
				fItems[i].draw();

			for (int i = 0; i < 32; i++)
				iItems[i].draw();	

			for (int i = 0; i < 32; i++)
				btItems[i].draw();
		}
	}

	bool isActive()
	{
		return this->active;
	}

	void setActive(bool act)
	{
		active = act;
	}

	void setSize(int x, int y)
	{
		rMain.setSize(sf::Vector2f(x, y));
	}

	sf::Vector2f getSize()
	{
		return rMain.getSize();
	}

	sf::Vector2f getPosition()
	{
		return rMain.getPosition();
	}

private:
	void resize()
	{
		int counter = 0;
		for (int i = 0; i < 32; i++)
		{
			if (bItems[i].isActive())
				counter++;

			if (fItems[i].isActive())
				counter++;

			if (iItems[i].isActive())
				counter++;

			if (btItems[i].isActive())
				counter++;

			rMain.setSize(sf::Vector2f(rMain.getSize().x, counter * 20 + (sCount * 20)));
		}
	}
};
#endif