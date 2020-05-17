#pragma once
#include <string>
#include <fstream>
#include <random>
#include <limits>
#include <thread>
#include <Windows.h>

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

namespace Key
{
	namespace Down
	{
		void W() { keybd_event(0x57, 0x11, 0, 0); }
		void A() { keybd_event(0x41, 0x1E, 0, 0); }
		void S() { keybd_event(0x53, 0x1F, 0, 0); }
		void D() { keybd_event(0x44, 0x20, 0, 0); }
		void Space() { keybd_event(MapVirtualKey(0x20, 0), 0x39, 0, 0); }

		void LMouse(){
			INPUT    Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}

	namespace Up
	{
		void W() { keybd_event(0x57, 0x11, KEYEVENTF_KEYUP, 0); }
		void A() { keybd_event(0x41, 0x1E, KEYEVENTF_KEYUP, 0); }
		void S() { keybd_event(0x53, 0x1F, KEYEVENTF_KEYUP, 0); }
		void D() { keybd_event(0x44, 0x20, KEYEVENTF_KEYUP, 0); }
		void Space() { keybd_event(MapVirtualKey(0x20, 0), 0x39, KEYEVENTF_KEYUP, 0); }

		void LMouse(){
			INPUT    Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}
}