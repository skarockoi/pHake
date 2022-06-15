#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include "Globals.hpp"

bool ReadSignatures(); // read out signatures
bool ReadConfig(); // read config file
void ExitProgram(); // clean up, exit

void StartCheats();
void StartUI();

int main()
{
	if (!proc.AttachProcess("GTA5.exe")) // trying to find gta process
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	if (!ReadSignatures()) // check if pointers were found, if not the game version has changed
	{
		MessageBox(NULL, "game version does not match cheat version (1.60) ", "Error", NULL);
		return false;
	}

	if (!ReadConfig())
	{
		MessageBox(NULL, "config file could not be read, restoring...", "Error", NULL);
	}

	StartCheats();
	StartUI(); 
	ExitProgram();
}
#endif