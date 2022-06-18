#include "pList.hpp"
#include "pFont.hpp"

#define TEXT_SIZE 16
#define TEXT_COLOR sf::Color::Color(255, 255, 255, 255)

#define ITEM_HEIGHT 20
#define ITEM_WIDTH 48

#define BACK_WIDTH 208

#define DISTANCE_FROM_EDGE 2

pList::pList() :
	window_(0),
	font_(),
	rect_back_({0,0}),
	items_name_(0),
	items_bool_(0),
	items_float_(0),
	items_int_(0),
	items_string_(0),
	items_button_(0),
	item_count_(0),
	gap_count_(0),
	active_(false),
	used_(false)
{ }

void pList::Create(sf::RenderWindow* const& Window)
{
	window_ = Window;
	font_.loadFromMemory(&Pixellari, Pixellari.size());

	rect_back_.setSize(sf::Vector2f(BACK_WIDTH, 0));
	rect_back_.setFillColor(sf::Color::Color(0, 0, 0, 150));
	rect_back_.setOutlineColor(sf::Color::Color(0, 0, 0));
	rect_back_.setOutlineThickness(1);
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
	buffer.size(sf::Vector2f(ITEM_WIDTH, ITEM_HEIGHT));
	buffer.position(sf::Vector2f(rect_back_.getSize().x - buffer.size().x + rect_back_.getPosition().x - DISTANCE_FROM_EDGE, rect_back_.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT)));

	items_float_.push_back(buffer);

	AddWord(name);
	resize();
}

void pList::AddInt(const std::string& name, uint32_t& value, int inc, int dec)
{
	pItemInt buffer;
	buffer.Create(window_, &font_);
	buffer.AddValue(value, inc, dec);
	buffer.size(sf::Vector2f(ITEM_WIDTH, ITEM_HEIGHT));
	buffer.position(sf::Vector2f(rect_back_.getSize().x - buffer.size().x + rect_back_.getPosition().x - DISTANCE_FROM_EDGE, rect_back_.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT)));

	items_int_.push_back(buffer);

	AddWord(name);
	resize();
}

void pList::AddBool(const std::string& name, bool& value)
{
	pItemBool buffer;
	buffer.Create(window_, &font_);
	buffer.AddValue(value);
	buffer.size(sf::Vector2f(ITEM_WIDTH, ITEM_HEIGHT));
	buffer.position(sf::Vector2f(rect_back_.getSize().x - buffer.size().x + rect_back_.getPosition().x - DISTANCE_FROM_EDGE, rect_back_.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT)));

	items_bool_.push_back(buffer);

	AddWord(name);
	resize();
}

void pList::AddFunction(const std::string& name, void(&functionP)())
{
	pButton buffer;
	buffer.Create(window_, &font_);
	buffer.Connect(functionP);
	buffer.size(ITEM_WIDTH, ITEM_HEIGHT - 2);
	buffer.position(rect_back_.getSize().x - buffer.size().x + rect_back_.getPosition().x - DISTANCE_FROM_EDGE, rect_back_.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT + 2));

	items_button_.push_back(buffer);

	AddWord(name);
	resize();
}

void pList::AddString(const std::string& name, std::string& value)
{
	pItemString buffer;
	buffer.Create(window_, &font_);

	buffer.AddValue(value);
	buffer.size(sf::Vector2f(ITEM_WIDTH, ITEM_HEIGHT));
	buffer.position(sf::Vector2f(rect_back_.getSize().x - buffer.size().x + rect_back_.getPosition().x - DISTANCE_FROM_EDGE, rect_back_.getPosition().y + DISTANCE_FROM_EDGE + ((gap_count_ * 5) + item_count_ * ITEM_HEIGHT)));

	items_string_.push_back(buffer);

	AddWord(name);
	resize();
}

void pList::Loop()
{
	if (!active_)
		return;
	
	if (!used_)
		return;
	
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

void pList::Draw()
{
	if (!active_)
		return;

	if (!used_)
		return;

	window_->draw(rect_back_);

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

void pList::AddGap()
{
	gap_count_++;
}

void pList::position(sf::Vector2f xy)
{
	rect_back_.setPosition(xy.x, xy.y);
}

void pList::size(sf::Vector2f xy)
{
	rect_back_.setSize(sf::Vector2f(xy.x, xy.y));
}

sf::Vector2f pList::size()
{
	return rect_back_.getSize();
}

sf::Vector2f pList::position()
{
	return rect_back_.getPosition();
}

void pList::AddWord(const std::string& name)
{
	if (!used_)
		used_ = true;

	sf::Text buffer;
	buffer.setFont(font_);
	buffer.setCharacterSize(TEXT_SIZE);
	buffer.setFillColor(TEXT_COLOR);
	buffer.setPosition(rect_back_.getPosition().x + DISTANCE_FROM_EDGE, rect_back_.getPosition().y + ((gap_count_ * 5) + DISTANCE_FROM_EDGE + item_count_ * ITEM_HEIGHT));
	buffer.setString(name);

	items_name_.push_back(buffer);

	item_count_++;
}

bool pList::used()
{
	return used_;
}

bool pList::active()
{
	return active_;
}

void pList::resize()
{
	rect_back_.setSize(sf::Vector2f(rect_back_.getSize().x, ((items_name_.size() * ITEM_HEIGHT) + (gap_count_ * 5) + DISTANCE_FROM_EDGE + 1)));
}