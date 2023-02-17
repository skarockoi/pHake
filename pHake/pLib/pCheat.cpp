#include "pHake.hpp"
#include "pCheat.hpp"
#include <iostream>

pCheat::pCheat(std::shared_ptr<pHake> phake) : name_("Default") { this->phake = phake; }
void pCheat::Execute() {}
void pCheat::Restore() {}

pCheatLoop::pCheatLoop(std::shared_ptr<pHake> phake) : name_("Default"), thread_intervals_(0), active(0) { this->phake = phake; }
void pCheatLoop::Execute() {}
void pCheatLoop::Restore() {}