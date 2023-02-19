#include "pMenu.hpp"
#include "pCheat.hpp"
#include <iostream>

pMenu::pMenu() {  }

void pMenu::Attach(LPCSTR window_name)
{
	ui = std::make_unique<pOverlay>(); // initialize game UI
	ui->Create(window_name);  // overlay gta window
}

void pMenu::Add(std::shared_ptr<pCheatLoop> cheat)
{
	cheats_loop_.push_back(cheat);
	ui->list.AddBool(cheat->name_, *cheat->active);
}

void pMenu::Add(std::shared_ptr<pCheat> cheat)
{
	cheats_.push_back(cheat);
	ui->list.AddFunction(cheat->name_, [=]() { cheat->Execute(); });
}
void pMenu::Start()
{
	ui->list.AddFunction("Exit", [=]() {Stop(); });

	for (auto& i : this->cheats_loop_)
		this->threads_.push_back(pThread([&]() { i->Execute(); }, i->thread_intervals_));

	ui->Loop(); // main loop
}

void pMenu::Stop()
{
	for (auto& i : this->threads_)
		i.Destroy();

	for (auto& i : this->cheats_)
		i->Restore();
		
	ui->Close(); // close UI
}