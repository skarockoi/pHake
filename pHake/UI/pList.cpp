#include "pList.hpp"

#define TEXT_SIZE 16
#define TEXT_COLOR sf::Color::Color(255, 255, 255, 255)

#define ITEM_HEIGHT 20
#define ITEM_WIDTH 48

#define BACK_WIDTH 208

#define DISTANCE_FROM_EDGE 2

void pList::Create(sf::RenderWindow* const& Window)
{
	this->window_ = Window;
	this->font_.loadFromFile("Settings/font.ttf");

	this->rect_back.setSize(sf::Vector2f(BACK_WIDTH, 0));
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
	buffer.Create(window_, &font_);
	buffer.AddValue(value, inc, dec);
	buffer.size(ITEM_WIDTH, ITEM_HEIGHT);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x - DISTANCE_FROM_EDGE, rect_back.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT));

	items_float_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddInt(const std::string& name, uint32_t& value, int inc, int dec)
{
	pItemInt buffer;
	buffer.Create(window_, &font_);
	buffer.AddValue(value, inc, dec);
	buffer.size(ITEM_WIDTH, ITEM_HEIGHT);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x - DISTANCE_FROM_EDGE, rect_back.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT));

	items_int_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddBool(const std::string& name, bool& value)
{
	pItemBool buffer;
	buffer.Create(window_, &font_);
	buffer.AddValue(value);
	buffer.size(ITEM_WIDTH, ITEM_HEIGHT);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x - DISTANCE_FROM_EDGE, rect_back.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT));

	items_bool_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddFunction(const std::string& name, void(&functionP)())
{
	pButton buffer;
	buffer.Create(window_, &font_);
	buffer.Connect(functionP);
	buffer.size(ITEM_WIDTH, ITEM_HEIGHT - 2);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x - DISTANCE_FROM_EDGE, rect_back.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT + 2));

	items_button_.push_back(buffer);

	this->AddWord(name);
	this->resize();
}

void pList::AddString(const std::string& name, std::string& value)
{
	pItemString buffer;
	buffer.Create(window_, &font_);

	buffer.AddValue(value);
	buffer.size(ITEM_WIDTH, ITEM_HEIGHT);
	buffer.position(rect_back.getSize().x - buffer.size().x + rect_back.getPosition().x - DISTANCE_FROM_EDGE, rect_back.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT));

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
	buffer.setCharacterSize(TEXT_SIZE);
	buffer.setFillColor(TEXT_COLOR);
	buffer.setPosition(this->rect_back.getPosition().x + DISTANCE_FROM_EDGE, this->rect_back.getPosition().y + ((this->gap_count_ * 5) + DISTANCE_FROM_EDGE + this->item_count_ * ITEM_HEIGHT));
	buffer.setString(name);

	items_name_.push_back(buffer);

	item_count_++;
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
	this->active_ = act;
}

void pList::resize()
{
	this->rect_back.setSize(sf::Vector2f(this->rect_back.getSize().x, ((this->items_name_.size() * ITEM_HEIGHT) + (this->gap_count_ * 5) + DISTANCE_FROM_EDGE + 1)));
}

void pList::used(bool act)
{
	this->used_ = act;
}