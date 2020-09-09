#include "pList.hpp"

void pList::create(sf::RenderWindow* const& Window)
{
	this->window = Window;
	this->font.loadFromFile("Settings/font.ttf");

	this->rect_back.setSize(sf::Vector2f(208, 0));
	this->rect_back.setFillColor(sf::Color::Color(0, 0, 0, 150));
	this->rect_back.setOutlineColor(sf::Color::Color(0, 0, 0));
	this->rect_back.setOutlineThickness(1);
}

void pList::toggle()
{
	active = not active;
}

void pList::addFloat(const std::string& name, float& value, float inc, float dec)
{
	pItemFloat buffer;
	buffer.create(window);
	buffer.setFont(font);
	buffer.addPtr(value, inc, dec);
	buffer.setFixedSize(48, 20);
	buffer.setPosition(rect_back.getSize().x - buffer.getSize().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));
	buffer.setFillColor(sf::Color::Color(255, 255, 255, 255));

	items_float.push_back(buffer);

	this->addWord(name);
	this->resize();
}

void pList::addFloat(const std::string& name, float& value, float inc, float dec, uint8_t prec)
{
	pItemFloat buffer;
	buffer.create(window);
	buffer.setFont(font);
	buffer.addPtr(value, inc, dec);
	buffer.setPrecision(prec);
	buffer.setFixedSize(48, 20);
	buffer.setPosition(rect_back.getSize().x - buffer.getSize().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));
	buffer.setFillColor(sf::Color::Color(255, 255, 255, 255));

	items_float.push_back(buffer);

	this->addWord(name);
	this->resize();
}

void pList::addInt(const std::string& name, int& value, int inc, int dec)
{
	pItemInt buffer;
	buffer.create(window);
	buffer.setFont(font);
	buffer.addPtr(value, inc, dec);
	buffer.setFixedSize(48, 20);
	buffer.setPosition(rect_back.getSize().x - buffer.getSize().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));
	buffer.setFillColor(sf::Color::Color(255, 255, 255, 255));

	items_int.push_back(buffer);

	this->addWord(name);
	this->resize();
}

void pList::addBool(const std::string& name, bool& value)
{
	pItemBool buffer;
	buffer.create(window);
	buffer.setFont(font);
	buffer.addPtr(value, 1, 1);
	buffer.setFixedSize(48, 20);
	buffer.setPosition(rect_back.getSize().x - buffer.getSize().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));
	buffer.setFillColor(sf::Color::Color(255, 255, 255, 255));

	items_bool.push_back(buffer);

	this->addWord(name);
	this->resize();
}

void pList::addFunction(const std::string& name, void(&functionP)())
{
	pButton buffer;
	buffer.create(window);
	buffer.setFont(font);
	buffer.connect(functionP);
	buffer.setFixedSize(48, 19);
	buffer.setPosition(rect_back.getSize().x - buffer.getSize().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));

	items_button.push_back(buffer);

	this->addWord(name);
	this->resize();
}

void pList::addString(const std::string& name, std::string& value)
{
	pItemString buffer;
	buffer.create(window);
	buffer.setFont(font);
	buffer.addPtr(value);
	buffer.setFixedSize(48, 20);
	buffer.setPosition(rect_back.getSize().x - buffer.getSize().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));

	items_string.push_back(buffer);

	this->addWord(name);
	this->resize();
}

void pList::loop()
{
	if (this->isActive() && this->isUsed())
	{
		for (int i = 0; i < items_bool.size(); i++)
			items_bool[i].loop();

		for (int i = 0; i < items_float.size(); i++)
			items_float[i].loop();

		for (int i = 0; i < items_int.size(); i++)
			items_int[i].loop();

		for (int i = 0; i < items_button.size(); i++)
			items_button[i].loop();

		for (int i = 0; i < items_string.size(); i++)
			items_string[i].loop();
	}
}

void pList::draw()
{
	if (this->isActive() && this->isUsed())
	{
		window->draw(rect_back);

		for (int i = 0; i < items_name.size(); i++)
			window->draw(items_name[i]);

		for (int i = 0; i < items_bool.size(); i++)
			items_bool[i].draw();

		for (int i = 0; i < items_float.size(); i++)
			items_float[i].draw();

		for (int i = 0; i < items_int.size(); i++)
			items_int[i].draw();

		for (int i = 0; i < items_button.size(); i++)
			items_button[i].draw();

		for (int i = 0; i < items_string.size(); i++)
			items_string[i].draw();
	}
}

void pList::addGap()
{
	gapCount++;
}

void pList::setPosition(float x, float y)
{
	rect_back.setPosition(x, y);
}

void pList::setSize(float x, float y)
{
	rect_back.setSize(sf::Vector2f(x, y));
}

sf::Vector2f pList::getSize()
{
	return rect_back.getSize();
}

sf::Vector2f pList::getPosition()
{
	return rect_back.getPosition();
}

void pList::addWord(const std::string& name)
{
	if (!this->isUsed())
		setUsed(true);

	sf::Text buffer;
	buffer.setFont(font);
	buffer.setCharacterSize(16);
	buffer.setFillColor(sf::Color::Color(255, 255, 255, 255));
	buffer.setPosition(rect_back.getPosition().x, rect_back.getPosition().y + ((gapCount * 5) + count * 20));
	buffer.setString(name);

	items_name.push_back(buffer);

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
	rect_back.setSize(sf::Vector2f(rect_back.getSize().x, (items_name.size() * 20) + (gapCount * 5)));
}

void pList::setUsed(bool act)
{
	used = act;
}