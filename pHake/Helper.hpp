#pragma once
#include <string>
#include <fstream>
#include <random>
#include <limits>

void sleep(uint32_t ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

uint32_t SpawnRandomNumber(uint32_t min, uint32_t max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> num(min, max);
	return num(rng);
}

void LeftMouseDown()
{
	INPUT    Input = { 0 };

	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	::SendInput(1, &Input, sizeof(INPUT));
}

void LeftMouseUp()
{
	INPUT    Input = { 0 };

	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

void SendSpaceDown()
{
	keybd_event(MapVirtualKey(0x20, 0), 0x39, KEYEVENTF_EXTENDEDKEY, 0);
}

void SendSpaceUp()
{
	keybd_event(MapVirtualKey(0x20, 0), 0x39, KEYEVENTF_KEYUP, 0);
}

void SendWKeyDown()
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = 0x57;
	ip.ki.wScan = 0x11;
	ip.ki.dwFlags = 0;

	SendInput(1, &ip, sizeof(INPUT));
}

void SendWKeyUp()
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = 0x57;
	ip.ki.wScan = 0x11;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, &ip, sizeof(INPUT));
}

void SendKeyDown(WORD Key)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = Key;
	ip.ki.wScan = Key;
	ip.ki.dwFlags = 0;

	SendInput(1, &ip, sizeof(INPUT));
}
void SendKeyUp(WORD Key)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = Key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, &ip, sizeof(INPUT));
}
