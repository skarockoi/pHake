#ifndef _PWINDOW_HPP_
#define _PWINDOW_HPP_

#include "pButton.hpp"
#include "pItem.hpp"
#include "pList.hpp"
#include "pMouse.hpp"

#include <SFML/Graphics.hpp>
#pragma comment (lib, "Dwmapi.lib")

class pWindow
{
private:
	sf::RenderWindow window_;
	sf::Font		 font_;
	std::unique_ptr <pMouse> mouse_;

public:
	std::unique_ptr<pList> list;

	void Create();
	void Loop();

private:
	void FixSize();
};
#endif