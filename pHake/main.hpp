#include "Globals.hpp" // for MessageBox()

bool AlreadyRunning(); // check if cheat is already running
bool ReadSignatures(); // finds all needed signatures
bool ReadSettings(); // reads settings file and stores it in settings
bool InitializeCheats(); // attaches to the game and calls cheat constructors

void StartThreads(); // every program function that needs a constant loop has its own thread
void ExitProgram(); // closes threads, restores changed made to the game


int main()
{
	if (!AlreadyRunning())
	{
		MessageBox(NULL, "pHake is already running", "Error", NULL);
		return false;
	}

	if (!InitializeCheats())
	{
		MessageBox(NULL, "could not find the game", "Error", NULL);
		return false;
	}

	if (!ReadSignatures())
	{
		MessageBox(NULL, "game version does not match cheat version (1.60) ", "Error", NULL);
		return false;
	}

	if (!ReadSettings())
	{
		MessageBox(NULL, "settings file could not be read, restoring...", "Note", NULL);
	}

	StartThreads();
	ExitProgram();
}