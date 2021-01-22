#include "pList.hpp"

void pList::Create(sf::RenderWindow* const& Window)
{
	this->window_ = Window;
	this->font_.loadFromFile("Settings/font.ttf");

	this->rect_back.setSize(sf::Vector2f(208, 0));
	this->rect_back.setFillColor(sf::Color::Color(0, 0, 0, 150));
	this->rect_back.setOutlineColor(sf::Color::Color(0, 0, 0));
	this->rect_back.setOutlineThickness(1);
}

void pList::Toggle()
{
	active_ = not active_;
}

void pList::AddFloat(const std::string& name, float& value, float inc, float dec)
{
	pItemFloat buffer;
	buffer.Create(window_);
	buffer.font(font_);
	buffer.AddPtr(value, inc, dec);
	buffer.size(48, 20);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));
	buffer.fill_color(sf::Color::Color(255, 255, 255, 255));

	items_float_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddFloat(const std::string& name, float& value, float inc, float dec, uint8_t prec)
{
	pItemFloat buffer;
	buffer.Create(window_);
	buffer.font(font_);
	buffer.AddPtr(value, inc, dec);
	buffer.precision(prec);
	buffer.size(48, 20);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));
	buffer.fill_color(sf::Color::Color(255, 255, 255, 255));

	items_float_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddInt(const std::string& name, int& value, int inc, int dec)
{
	pItemInt buffer;
	buffer.Create(window_);
	buffer.font(font_);
	buffer.AddPtr(value, inc, dec);
	buffer.size(48, 20);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));
	buffer.fill_color(sf::Color::Color(255, 255, 255, 255));

	items_int_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddBool(const std::string& name, bool& value)
{
	pItemBool buffer;
	buffer.Create(window_);
	buffer.font(font_);
	buffer.AddPtr(value, 1, 1);
	buffer.size(48, 20);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));
	buffer.fill_color(sf::Color::Color(255, 255, 255, 255));

	items_bool_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddFunction(const std::string& name, void(&functionP)())
{
	pButton buffer;
	buffer.Create(window_);
	buffer.font(font_);
	buffer.Connect(functionP);
	buffer.fixed_size(48, 19);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));

	items_button_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddString(const std::string& name, std::string& value)
{
	pItemString buffer;
	buffer.Create(window_);
	buffer.font(font_);
	buffer.AddPtr(value);
	buffer.size(48, 20);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));

	items_string_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::Loop()
{
	if (this->active() && this->used())
	{
		for (int i = 0; i < items_bool_.size(); i++)
			items_bool_[i].Loop();

		for (int i = 0; i < items_float_.size(); i++)
			items_float_[i].Loop();

		for (int i = 0; i < items_int_.size(); i++)
			items_int_[i].Loop();

		for (int i = 0; i < items_button_.size(); i++)
			items_button_[i].Loop();

		for (int i = 0; i < items_string_.size(); i++)
			items_string_[i].Loop();
	}
}

void pList::Draw()
{
	if (this->active() && this->used())
	{
		window_->draw(rect_back);

		for (int i = 0; i < items_name_.size(); i++)
			window_->draw(items_name_[i]);

		for (int i = 0; i < items_bool_.size(); i++)
			items_bool_[i].Draw();

		for (int i = 0; i < items_float_.size(); i++)
			items_float_[i].Draw();

		for (int i = 0; i < items_int_.size(); i++)
			items_int_[i].Draw();

		for (int i = 0; i < items_button_.size(); i++)
			items_button_[i].Draw();

		for (int i = 0; i < items_string_.size(); i++)
			items_string_[i].Draw();
	}
}

void pList::AddGap()
{
	gap_count_++;
}

void pList::position(float x, float y)
{
	rect_back.setPosition(x, y);
}

void pList::size(float x, float y)
{
	rect_back.setSize(sf::Vector2f(x, y));
}

sf::Vector2f pList::size()
{
	return rect_back.getSize();
}

sf::Vector2f pList::position()
{
	return rect_back.getPosition();
}

void pList::AddWord(const std::string& name)
{
	if (!this->used())
		used(true);

	sf::Text buffer;
	buffer.setFont(font_);
	buffer.setCharacterSize(16);
	buffer.setFillColor(sf::Color::Color(255, 255, 255, 255));
	buffer.setPosition(rect_back.getPosition().x, rect_back.getPosition().y + ((gap_count_ * 5) + count_ * 20));
	buffer.setString(name);

	items_name_.push_back(buffer);

	count_++;
}

bool pList::used()
{
	return this->used_;
}

bool pList::active()
{
	return this->active_;
}

void pList::active(bool act)
{
	active_ = act;
}

void pList::resize()
{
	rect_back.setSize(sf::Vector2f(rect_back.getSize().x, (items_name_.size() * 20) + (gap_count_ * 5)));
}

void pList::used(bool act)
{
	used_ = act;
}