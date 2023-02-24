#ifndef PHAKE_HPP
#define PHAKE_HPP

#include "Ui/pOverlay.hpp"

#include <Windows.h>

#include <string>
#include <vector>

#include "pThread.hpp"

class pCheat;
class pCheatLoop;

class pMenu
{
public:
	std::shared_ptr<pOverlay> ui;

public:
	pMenu();
	void Attach(LPCSTR window_name);
	void Add(std::shared_ptr<pCheat> cheat);
	void Add(std::shared_ptr<pCheatLoop> cheat);

	void Start();
	void Stop();

private:
	std::vector<std::shared_ptr<pCheat>> cheats_;
	std::vector<std::shared_ptr<pCheatLoop>> cheats_loop_;
	std::vector<pThread> threads_;
};
#endif