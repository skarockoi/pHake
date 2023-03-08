#include "pCheat.hpp"

#include <iostream>

pCheat::pCheat() : name_("Default") {}
void pCheat::Execute() {}
void pCheat::Restore() {}

pCheatLoop::pCheatLoop() : name_("Default"), thread_intervals_(0), active_(0) {}
void pCheatLoop::Execute() {}
void pCheatLoop::Restore() {}