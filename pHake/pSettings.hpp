#ifndef _PSETTINGS_HPP_
#define _PSETTINGS_HPP_

#include <fstream>
#include <filesystem>
#include <string>

class pSettings
{
private:
	std::vector<std::string>* fileContent;
	std::string filePath;
public:
	pSettings() {}
	pSettings(const std::string filePathAndName)
	{
		filePath = filePathAndName;

		if (std::filesystem::exists(filePathAndName)) // Check if the cfg file exitst, otherwise create a new file(does not work if the path is behind a directory that does not exist
		{
			filePath = filePathAndName;

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
			std::ofstream file{ filePathAndName };
			file.close();
		}
	}

	std::string addGet(std::string Key, std::string Value)
	{
		if (this->checkExistanceOfKey(Key))
		{
			return this->getKeyByName(Key);
		}
		else
		{
			this->addKeyAndValue(Key, Value);
			return this->getKeyByName(Key);
		}
	}

	bool edit(std::string Key, std::string Value)
	{
		if (this->checkExistanceOfKey(Key))
		{
			this->changeKeyValue(Key, Value);
			return true;
		}
		return false;
	}

	void save()
	{
		this->deleteAndSaveToFile();
		fileContent->clear();
		delete fileContent;
	}

	void clear()
	{
		std::ofstream del;
		del.open(this->filePath, std::ofstream::out | std::ofstream::trunc);
		del.close();
	}

private:
	void addKeyAndValue(std::string Key, std::string Value)
	{
		this->fileContent->push_back(Key + " = " + Value);
	}

	std::string getKeyByName(std::string Key)
	{
		for (size_t i = 0; i < this->fileContent->size(); i++)
		{
			if ((*fileContent)[i].find(Key) != std::string::npos)
				return (*fileContent)[i].substr((*fileContent)[i].find("=") + 1);

		}
		return "";
	}

	bool checkExistanceOfKey(std::string Key)
	{
		for (size_t i = 0; i < this->fileContent->size(); i++)
		{
			if ((*fileContent)[i].find(Key) != std::string::npos) {
				return true;
			}
		}
		return false;
	}

	void changeKeyValue(std::string Key, std::string Value)
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

	void deleteAndSaveToFile()
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
};
#endif