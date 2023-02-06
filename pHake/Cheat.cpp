#include "Globals.hpp"

#include "Cheat.hpp"
#include <iostream>

Cheat::Cheat(std::shared_ptr<pHake> phake) : name_("Default") { this->phake = phake; }
void Cheat::Execute() {}
void Cheat::Restore() {}

CheatLoop::CheatLoop(std::shared_ptr<pHake> phake) : name_("Default"), thread_intervals_(0), active(0) { this->phake = std::make_shared<pHake>(phake); }
void CheatLoop::Execute() {}
void CheatLoop::Restore() {}