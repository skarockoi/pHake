#include "pList.hpp"

void pList::create(sf::RenderWindow* const& window)
{
	this->Window = window;
	this->Font.loadFromFile("Settings/font.ttf");

	this->Pos.x = 0;
	this->Pos.y = 0;

	this->rectBack.setSize(sf::Vector2f(208, 0));
	this->rectBack.setPosition(Pos.x, Pos.y);
	this->rectBack.setFillColor(sf::Color::Color(0, 0, 0, 150));
	this->rectBack.setOutlineColor(sf::Color::Color(0, 0, 0));
	this->rectBack.setOutlineThickness(1);

}

void pList::toggle()
{
	active = not active;
}

void pList::addFloat(const std::string& name, float& value, float inc, float dec)
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

void pList::addFloat(const std::string& name, float& value, float inc, float dec, uint8_t prec)
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

void pList::addInt(const std::string& name, int& value, int inc, int dec)
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

void pList::addBool(const std::string& name, bool& value)
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

void pList::addFunction(const std::string& name, void(&functionP)())
{
	pButton tempButton;
	tempButton.create(Window);
	tempButton.setFont(Font);
	tempButton.connect(functionP);
	tempButton.setFixedSize(48, 19);
	tempButton.setPosition(rectBack.getSize().x - tempButton.getSize().x + rectBack.getPosition().x, rectBack.getPosition().y + ((gapCount * 5) + count * 20));
	itemButton.push_back(tempButton);

	this->addWord(name);
	this->resize();
}

void pList::addString(const std::string& name, std::string& value)
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

void pList::loop()
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
			itemButton[i].loop();

		for (int i = 0; i < itemString.size(); i++)
			itemString[i].loop();
	}
}

void pList::draw()
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

void pList::addGap()
{
	gapCount++;
}


void pList::setPosition(int x, int y)
{
	rectBack.setPosition(x, y);
}

void pList::setSize(int x, int y)
{
	rectBack.setSize(sf::Vector2f(x, y));
}

sf::Vector2f pList::getSize()
{
	return rectBack.getSize();
}

sf::Vector2f pList::getPosition()
{
	return rectBack.getPosition();
}

void pList::addWord(const std::string& name)
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

bool pList::isUsed()
{
	return this->used;
}

bool pList::isActive()
{
	return this->active;
}

void pList::setActive(bool act)
{
	active = act;
}

void pList::resize()
{
	rectBack.setSize(sf::Vector2f(rectBack.getSize().x, (itemName.size() * 20) + (gapCount * 5)));
}

void pList::setUsed(bool act)
{
	used = act;
}