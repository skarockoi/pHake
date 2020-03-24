#pragma once
#include <string>
#include <fstream>
#include <limits>

struct vector2
{
	float x, y;
};

struct vector3
{
	float x, y, z;
};

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

void SendKeyDown(WORD Key)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = Key;
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

float distance3d(float from_x, float from_y, float from_z, float to_x, float to_y, float to_z)
{
	float x = from_x - to_x;
	float y = from_y - to_y;
	float z = from_z - to_z;

	return sqrt(x * x + y * y + z * z);
}

float distance2d(float from_x, float from_y, float to_x, float to_y)
{
	float x = from_x - to_x;
	float y = from_y - to_y;

	return sqrt(x * x + y * y);
}

std::string GetLineContent(int Line, std::ifstream& FileToRead)
{
	std::string LineContent;

	for (int i = 1; i <= Line; i++)
	{
		std::getline(FileToRead, LineContent);
	}

	FileToRead.clear();
	FileToRead.seekg(0, std::ios::beg);

	return LineContent;
}