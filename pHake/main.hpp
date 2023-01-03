#include "Globals.hpp" // for MessageBox()

bool AlreadyRunning(); // check if cheat is already running
bool AttachToGTA(); // attaches to the game
bool ReadSignatures(); // finds all needed signatures

void Start(); // Start Cheat Manager

int main()
{
	if (!AlreadyRunning())
	{
		MessageBox(NULL, "pHake is already running", "Error", NULL);
		return false;
	}

	if (!AttachToGTA())
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	if (!ReadSignatures())
	{
		MessageBox(NULL, "game version does not match cheat version", "Error", NULL);
		return false;
	}

	Start();
}