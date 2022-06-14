#ifndef _PHELPER_HPP_
#define _PHELPER_HPP_

#include <string>
#include <fstream>
#include <random>
#include <limits>
#include <thread>
#include <filesystem>
#include <Windows.h>
#include <sstream>  
#include <iomanip>

inline void sleep(uint32_t ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

template <typename T>
void GetKeyExecuteWaitForRelease(int key, T function)
{
	if (HIBYTE(GetAsyncKeyState(key)))
	{
		function();
		while (HIBYTE(GetAsyncKeyState(key)))
			sleep(100);
	}
}

static uint32_t SpawnRandomNumber(uint32_t min, uint32_t max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> num(min, max);
	return num(rng);
}

static std::string CutStringBetweenTwoCharacters(std::string& origin, const std::string& left, const std::string& right)
{
	size_t first = origin.find(left);
	size_t last = origin.find(right);
	return origin.substr(first + 1, last - 1 - first);
}

static std::string GetStringBeforeCharacter(std::string& origin, const std::string& Character)
{
	std::string::size_type pos = origin.find(Character);
	if (pos != std::string::npos)
		return origin.substr(0, pos);
	else
		return origin;
}

static void SplitSpringByCharacterAndSaveToVector(std::vector<std::string>* Vector, const std::string& Origin, char Character)
{
	std::string token;
	std::istringstream tokenStream(Origin);
	while (std::getline(tokenStream, token, Character))
		Vector->push_back(token);
}

static std::vector<std::string> SplitSpringByCharacterAndSaveAsVector(const std::string& Origin, char Character)
{
	std::vector<std::string> the_vector;
	std::string token;
	std::istringstream tokenStream(Origin);
	while (std::getline(tokenStream, token, Character))
		the_vector.push_back(token);

	return the_vector;
}

static bool ReadFileByLineAndSaveToVector(std::vector<std::string>* Vector, const std::string& Filepath)
{
	if (std::filesystem::exists(Filepath)) // check if the cfg file exists, otherwise create a new file (does not work if the path is behind a directory that does not exist
	{
		std::ifstream file(Filepath);

		std::string   tempStr;
		while (std::getline(file, tempStr))
		{
			if (tempStr.size() > 0)
				Vector->push_back(tempStr); // read cfg file into vector full of strings
		}
		return true;
	}
	else
		return false;

}

static std::string RandomString(size_t Size)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist('a', 'z');

	std::string result;
	std::generate_n(std::back_inserter(result), Size, [&] {return dist(mt); });

	return result;
}

namespace Key
{
	namespace Down
	{
		inline void W() { keybd_event(0x57, 0x11, 0, 0); }
		inline void A() { keybd_event(0x41, 0x1E, 0, 0); }
		inline void S() { keybd_event(0x53, 0x1F, 0, 0); }
		inline void D() { keybd_event(0x44, 0x20, 0, 0); }
		inline void Space() { keybd_event(MapVirtualKey(0x20, 0), 0x39, 0, 0); }

		static void LMouse(){
			INPUT    Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}

	namespace Up
	{
		inline void W() { keybd_event(0x57, 0x11, KEYEVENTF_KEYUP, 0); }
		inline void A() { keybd_event(0x41, 0x1E, KEYEVENTF_KEYUP, 0); }
		inline void S() { keybd_event(0x53, 0x1F, KEYEVENTF_KEYUP, 0); }
		inline void D() { keybd_event(0x44, 0x20, KEYEVENTF_KEYUP, 0); }
		inline void Space() { keybd_event(MapVirtualKey(0x20, 0), 0x39, KEYEVENTF_KEYUP, 0); }

		static void LMouse(){
			INPUT    Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			::SendInput(1, &Input, sizeof(INPUT));
		}
	}
}
#endif