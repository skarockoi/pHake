#include "Globals.hpp" // for MessageBox()

bool AlreadyRunning(); // check if cheat is already running
bool AttachToGTA(); // attaches to the game
bool ReadSignatures(); // finds all needed signatures
bool ReadSettings(); // reads settings file and stores it in settings

void Start(); // every program function that needs a constant loop has its own thread
void Exit(); // closes threads, restores changes made to the game

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

	if (!ReadSettings())
	{
		MessageBox(NULL, "settings file could not be read, restoring...", "Note", NULL);
	}

	Start();
	Exit();
}