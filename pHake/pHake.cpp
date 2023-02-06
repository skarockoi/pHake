#include "Globals.hpp"

#include "pHake.hpp"
#include "Cheat.hpp"
#include <iostream>

using namespace globals;

pHake::pHake() {  }

void pHake::Attach(LPCSTR Name, std::shared_ptr<Process> process)
{
	this->process = process;
	menu = std::make_unique<pOverlay>(); // initialize game UI
	menu->Create(Name);  // overlay gta window
}

void pHake::Add(Cheat& cheat)
{
	cheats_.push_back(cheat);
}

void pHake::Add(CheatLoop& cheat)
{
	cheats_loop_.push_back(cheat);
}


void pHake::Start()
{
	//menu->list.AddFunction("Exit", this->Stop);

	for (auto& i : this->cheats_loop_)
		this->threads_.push_back(pThread([&]() { i.Execute(); }, i.thread_intervals_));
	
	menu->Loop(); // main loop
}

void pHake::Stop()
{
	for (auto& i : this->threads_)
		i.Destroy();

	for (auto& i : this->cheats_)
		i.Restore();
		
	process->Close(); // close handle to attached process
	menu->Close(); // close UI
}