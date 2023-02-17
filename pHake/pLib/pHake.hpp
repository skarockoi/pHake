#ifndef PHAKE_HPP
#define PHAKE_HPP

#include "pUi/pOverlay.hpp"

#include <Windows.h>

#include <string>
#include <vector>

#include "pThread.hpp"
#include "pMemory/pProcess.hpp"

class pCheat;
class pCheatLoop;

class pHake
{
public:
	std::shared_ptr<pProcess> process;
	std::unique_ptr<pOverlay> menu;

public:
	pHake();
	void Attach(LPCSTR window_name, std::shared_ptr<pProcess> process_name);
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