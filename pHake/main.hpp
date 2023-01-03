#include "Globals.hpp" // for MessageBox()

bool AlreadyRunning(); // check if cheat is already running
bool AttachToGTA(); // attaches to the game
bool ReadSignatures(); // finds all needed signatures


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

//	threads_.push_back(new pThread([=]() {
//		world.UpdateAll(phake->process.read<uintptr_t>(pointers.world)); // updates world info in loop
//	settings.kmh = 3.6f * phake->process.read<float>(pointers.kmh); // meters per second * 3.6 = km/h	
//		}, 1));


	pHake phake = pHake();

	GodMode godmode = GodMode();
	phake.Add(godmode);
	phake.Start();

	// TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS); // exit

}