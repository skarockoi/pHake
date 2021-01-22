#ifndef _POVERLAY_HPP_
#define _POVERLAY_HPP_

#include "pButton.hpp"
#include "pItem.hpp"
#include "pList.hpp"
#include "pMouse.hpp"
#include "pNotificationCenter.hpp"

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

struct GameInfo
{
private:
	HWND hwnd_;
	RECT rect_;
	LPCSTR game_;
	sf::Vector2i pos_;
	sf::Vector2u size_;

public:
	GameInfo() {}
	GameInfo(LPCSTR Game);

	void Update();
	bool IsActive();

	sf::Vector2i position(){ return sf::Vector2i(rect_.left, rect_.top); }
	sf::Vector2u size() { return sf::Vector2u(rect_.right - rect_.left, rect_.bottom - rect_.top); }
};

class pOverlay
{
private:
	sf::RenderWindow window_;
	sf::Font		 font_;
	GameInfo		 game_info_;
	pMouse			 mouse_;

public:
	pList				list_;
	pNotificationCenter notification_;

	void Create(LPCSTR Name);
	void Toggle();
	void Loop();
private:
	void SetWindowTransparentAndNotClickableEx(HWND handle);
	void FixPosition();
};
#endif