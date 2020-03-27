#ifndef _PLISTVIEW_HPP_
#define _PLISTVIEW_HPP_

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>
#include "pItem.hpp"
#include "pButton.hpp"

class pList
{
private:
	sf::RenderWindow* Window;
	sf::Font		   Font;
	sf::Vector2i	   Pos;
	sf::RectangleShape rMain;

	sf::Text wWord[32];
	sf::Text wItems[32];

	pItemBool bItems[32];
	pItemFloat fItems[32];
	pItemInt iItems[32];
	pItemString strItems[32];
	pButton btItems[32];


	uint8_t gapCount = 0;
	uint8_t strCount = 0;
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

	void add(std::string name)
	{
		wWord[count].setFont(Font);
		wWord[count].setCharacterSize(16);
		wWord[count].setFillColor(sf::Color::Color(255, 255, 255, 255));
		wWord[count].setPosition(rMain.getPosition().x, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		wWord[count].setString(name);
	}

	void addFloat(std::string name, float& value, float inc, float dec)
	{
		this->add(name);

		fItems[fCount].create(Window);
		fItems[fCount].addPtr(value, inc, dec);
		fItems[fCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		fItems[fCount].setFixedSize(48, 20);
		fItems[fCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		fCount++;
		count++;
		this->resize();
	}

	void addFloat(std::string name, float& value, float inc, float dec, uint8_t prec)
	{
		this->add(name);

		fItems[fCount].create(Window);
		fItems[fCount].addPtr(value, inc, dec);
		fItems[fCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		fItems[fCount].setFixedSize(48, 20);
		fItems[fCount].setPrecision(prec);
		fItems[fCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		fCount++;
		count++;
		this->resize();
	}

	void addInt(std::string name, int& value, int inc, int dec)
	{
		this->add(name);


		iItems[iCount].create(Window);
		iItems[iCount].addPtr(value, inc, dec);
		iItems[iCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		iItems[iCount].setFixedSize(48, 20);
		iItems[iCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		iCount++;
		count++;
		this->resize();
	}

	void addBool(std::string name, bool& value)
	{
		this->add(name);

		bItems[bCount].create(Window);
		bItems[bCount].addPtr(value, 1, 1);
		bItems[bCount].setPostion(160 + rMain.getPosition().x, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		bItems[bCount].setFixedSize(48, 20);
		bItems[bCount].setFillColor(sf::Color::Color(255, 255, 255, 255));

		bCount++;
		count++;
		this->resize();
	}


	void addFunction(std::string name, void(&functionP)())
	{
		this->add(name);

		btItems[btCount].create(Window);
		btItems[btCount].connect(functionP);
		btItems[btCount].setPostion(160 + rMain.getPosition().x - 1, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		btItems[btCount].setFixedSize(50, 19);

		btCount++;
		count++;
		this->resize();
	}

	void addString(std::string name, std::string& value)
	{
		this->add(name);

		strItems[strCount].create(Window);
		strItems[strCount].addPtr(value);
		strItems[strCount].setPostion(160 + rMain.getPosition().x - 1, rMain.getPosition().y + 2 + ((gapCount * 5) + count * 20));
		strItems[strCount].setFixedSize(50, 19);

		strCount++;
		count++;
		this->resize();
	}

	void addGap()
	{
		gapCount++;
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

			for (int i = 0; i < 32; i++)
				strItems[i].Loop();
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

			for (int i = 0; i < 32; i++)
				strItems[i].draw();
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

			if (strItems[i].isActive())
				counter++;

			rMain.setSize(sf::Vector2f(rMain.getSize().x, counter * 20 + (gapCount * 5) + 4));
		}
	}
};


#endif