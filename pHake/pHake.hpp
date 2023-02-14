#ifndef PHAKE_HPP
#define PHAKE_HPP

#include <Windows.h>

#include "UI/pThread.hpp"
#include <string>
#include <vector>

#include "Memory/Process.hpp"

class Cheat;
class CheatLoop;

class pHake
{
public:
	std::unique_ptr<pOverlay> menu;
	std::shared_ptr<Process> process;

public:
	pHake();
	void Attach(LPCSTR window_name, std::shared_ptr<Process> process_name);
	void Add(std::shared_ptr<Cheat> cheat);
	void Add(std::shared_ptr<CheatLoop> cheat);

	void Start();
	void Stop();

private:
	std::vector<std::shared_ptr<Cheat>> cheats_;
	std::vector<std::shared_ptr<CheatLoop>> cheats_loop_;
	std::vector<pThread> threads_;
};
#endif