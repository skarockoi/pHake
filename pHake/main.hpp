#include "Globals.hpp"

bool AlreadyRunning(); // check if cheat is already running
bool ReadSignatures(); // read out signatures
bool ReadSettings(); // read ini file
void ExitProgram(); // clean up, exit

void StartCheats();
void StartUI();

int main()
{
	if (!AlreadyRunning())
	{
		MessageBox(NULL, "pHake is already running", "Error", NULL);
		return false;
	}

	if (!proc.AttachProcess("GTA5.exe"))
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	if (!ReadSignatures()) // check if pointers were found, if not the game version has changed
	{
		MessageBox(NULL, "game version does not match cheat version (1.60) ", "Error", NULL);
		return false;
	}

	if (!ReadSettings())
	{
		MessageBox(NULL, "settings file could not be read, restoring...", "Note", NULL);
	}

	StartCheats();
	StartUI(); 
	ExitProgram();
}