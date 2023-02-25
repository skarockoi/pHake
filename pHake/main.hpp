#include "pLib/pMenu.hpp" // SFML is annoying and needs to be included first
#include <Windows.h> // for MessageBox()

bool AlreadyRunning(); // check if cheat is already running
bool Attach(); // attaches to the game
bool ReadSignatures(); // finds all needed signatures
bool ReadConfig(); // read ini file

bool Start(); // starts the cheat and ui

int main()
{
	if (!AlreadyRunning())
	{
		MessageBox(NULL, "pHake is already running", "Error", NULL);
		return false;
	}

	if (!Attach())
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	if (!ReadSignatures())
	{
		MessageBox(NULL, "game version does not match cheat version", "Error", NULL);
		return false;
	}

	if (!ReadConfig())
	{
		MessageBox(NULL, "settings file could not be read, restoring...", "Note", NULL);
	}

	return Start();
}