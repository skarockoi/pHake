#ifndef _PSETTINGS_HPP_
#define _PSETTINGS_HPP_

#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <sstream>

class pSettings // Simple class to store/read/change values
{
private:
	std::vector<std::string>* fileContent;
	std::string filePath;
public:
	pSettings() {}
	pSettings(const std::string filePathAndName);

	template <typename T>
	T				addGet(std::string Key, T Value);
	void			addComment(std::string Key);

	template <typename T>
	bool			edit(std::string Key, T Value);

	void			save(); // save current state of "fileContent" to file
	void			clear(); // clear "fileContent"

private:
	void			addKeyAndValue(std::string Key, std::string Value);
	std::string		getKeyByName(std::string Key);
	bool			checkExistanceOfKey(std::string Key);
	void			changeKeyValue(std::string Key, std::string Value);
	void			deleteAndSaveToFile();

	template <typename T>
	T lexical_cast(const std::string& str);
};


// public functions
pSettings::pSettings(const std::string filePathAndName)
{
	filePath = filePathAndName;

	if (std::filesystem::exists(filePathAndName)) // Check if the cfg file exitst, otherwise create a new file(does not work if the path is behind a directory that does not exist
	{
		fileContent = new std::vector<std::string>;
		std::ifstream file(filePathAndName);

		std::string   tempStr;
		while (std::getline(file, tempStr))
		{
			if (tempStr.size() > 0)
				fileContent->push_back(tempStr); // read cfg file into vector full of strings
		}

		for (size_t i = 0; i < fileContent->size(); i++)
		{
			(*fileContent)[i].erase(std::remove((*fileContent)[i].begin(), (*fileContent)[i].end(), '\n'), (*fileContent)[i].end()); // remove all "\n"s from strings
		}
	}
	else
	{
		fileContent = new std::vector<std::string>;
		std::ofstream file{ filePathAndName };
		file.close();
	}
}

template<typename T>
inline T pSettings::addGet(std::string Key, T Value)
{
	if (this->checkExistanceOfKey(Key))
	{
		return this->lexical_cast<T>(this->getKeyByName(Key));
	}
	else
	{
		this->addKeyAndValue(Key, std::to_string(Value));
		return this->lexical_cast<T>(this->getKeyByName(Key));
	}

	return 0;
}

void pSettings::addComment(std::string Key)
{
	if (!this->checkExistanceOfKey(Key))
	{
		this->fileContent->push_back(Key);
	}
}


template<typename T>
inline bool pSettings::edit(std::string Key, T Value)
{
	if (this->checkExistanceOfKey(Key))
	{
		this->changeKeyValue(Key, std::to_string(Value));
		return true;
	}
	return false;
}

void pSettings::save()
{
	this->deleteAndSaveToFile();
	fileContent->clear();
	delete fileContent;
}

void pSettings::clear()
{
	std::ofstream del;
	del.open(this->filePath, std::ofstream::out | std::ofstream::trunc);
	del.close();
}

// private functions
void pSettings::addKeyAndValue(std::string Key, std::string Value)
{
	this->fileContent->push_back(Key + " = " + Value);
}

std::string pSettings::getKeyByName(std::string Key)
{
	for (size_t i = 0; i < this->fileContent->size(); i++)
	{
		if ((*fileContent)[i].find(Key) != std::string::npos)
			return (*fileContent)[i].substr((*fileContent)[i].find("=") + 1);

	}
	return "";
}

bool pSettings::checkExistanceOfKey(std::string Key)
{
	for (size_t i = 0; i < this->fileContent->size(); i++)
	{
		if ((*fileContent)[i].find(Key) != std::string::npos) {
			return true;
		}
	}
	return false;
}
void pSettings::changeKeyValue(std::string Key, std::string Value)
{
	for (size_t i = 0; i < this->fileContent->size(); i++)
	{
		if ((*fileContent)[i].find(Key) != std::string::npos)
		{
			(*fileContent)[i].clear();
			(*fileContent)[i] = Key + " = " + Value;
		}
	}
}
void pSettings::deleteAndSaveToFile()
{
	std::ofstream del;
	del.open(this->filePath, std::ofstream::out | std::ofstream::trunc);
	del.close();

	std::ofstream file;
	file.open(this->filePath);

	for (size_t i = 0; i < this->fileContent->size(); i++)
	{
		file << (*fileContent)[i] + "\n";
	}
	file.close();
}

template<typename T>
inline T pSettings::lexical_cast(const std::string& str)
{
	T var;
	std::istringstream iss;
	iss.str(str);
	iss >> var;
	return var;
}
#endif