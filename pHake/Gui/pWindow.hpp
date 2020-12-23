#ifndef _PWINDOW_HPP_
#define _PWINDOW_HPP_

#include <SFML/Graphics.hpp>
#include "lib/pButton.hpp"
#include "lib/pItem.hpp"
#include "lib/pList.hpp"
#include "lib/pMouse.hpp"
#pragma comment (lib, "Dwmapi.lib")

class pWindow
{
private:
	sf::RenderWindow window_;
	sf::Font		 font_;
	pMouse			 mouse_;

public:
	pList			 list_;

	void Create();
	void Loop();

private:
	void FixSize();
};
#endif