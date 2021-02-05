#include "pOverlay.hpp"

#include <vector>

GameInfo::GameInfo(LPCSTR Game)
{
	game_ = Game;
	hwnd_ = FindWindowA(0, Game);
	GetWindowRect(hwnd_, &rect_);

	pos_ = this->position();
	size_ = this->size();
}

void GameInfo::Update()
{
	hwnd_ = FindWindowA(0, game_);
	GetWindowRect(hwnd_, &rect_);
	pos_ = this->position();
	size_ = this->size();
}

bool GameInfo::IsActive()
{
	if (this->hwnd_ != 0)
		return true;
	else
		return false;
}

void pOverlay::Create(LPCSTR Name)
{
	game_info_ = GameInfo(Name); // Getting game Info
	font_.loadFromFile("Settings/font.ttf");

	window_.create(sf::VideoMode(game_info_.size().x, game_info_.size().y), "pOverlay", sf::Style::None); // creating a window in the game's size 
	window_.setFramerateLimit(60);
	this->SetWindowTransparentAndNotClickableEx(window_.getSystemHandle()); // making the window transparent & not clickable

	notification.Create(&window_);

	mouse_.Create(&window_);
	mouse_.Toggle();

	list.Create(&window_);
	list.position(window_.getSize().x / 2, window_.getSize().y / 4);
	list.Toggle();
}

void pOverlay::Toggle()
{
	list.Toggle();
	mouse_.Toggle();

	if (list.active())
		sf::Mouse::setPosition(sf::Vector2i(list.position().x + window_.getPosition().x, list.position().y + window_.getPosition().y));
}

void pOverlay::Loop()
{
	while (window_.isOpen() && game_info_.IsActive())
	{
		this->FixPosition();

		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window_.setView(sf::View(visibleArea));
			}
		}

		list.Loop();
		mouse_.Loop();
		notification.Loop();

		window_.clear(sf::Color::Color(0, 0, 0, 0));

		list.Draw();
		mouse_.Draw();
		notification.Draw();

		window_.display();
	}
}

void pOverlay::SetWindowTransparentAndNotClickableEx(HWND handle)
{
	MARGINS margins;
	margins.cxLeftWidth = -1;
	LONG cur_style = GetWindowLong(handle, GWL_EXSTYLE);

	DwmExtendFrameIntoClientArea(handle, &margins);
	SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowLong(handle, GWL_EXSTYLE, cur_style | WS_EX_TRANSPARENT | WS_EX_LAYERED);
}

void pOverlay::FixPosition()
{
	game_info_.Update();
	sf::Vector2i game_pos = game_info_.position();
	sf::Vector2i window_pos = window_.getPosition();

	if (game_pos.x != window_pos.x + 1 || game_pos.y != window_pos.y - 1)
	{
		window_.setPosition(sf::Vector2i(game_pos.x - 1, game_pos.y + 1));
	}
}