#ifndef _PWINDOW_HPP_
#define _PWINDOW_HPP_

#include <SFML/Graphics.hpp>
#include "pButton.hpp"
#include "pItem.hpp"
#include "pList.hpp"
#include "pMouse.hpp"

#pragma comment (lib, "Dwmapi.lib")

class pWindow // same as pOverlay, but as an independet window
{
private:
	sf::RenderWindow window_;
	sf::Font		 font_;
	pMouse			 mouse_;

public:
	pList list;

	void Create();
	void Loop();
	void Close();

private:
	void FixSize();
};
#endif