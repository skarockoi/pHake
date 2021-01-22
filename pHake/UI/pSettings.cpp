#include "pSettings.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>

pSettings::~pSettings()
{
	delete[] this->file_content_;
}

pSettings::pSettings(const std::string& filePathAndName)
{
	this->file_path_ = filePathAndName;

	if (std::filesystem::exists(filePathAndName)) // check if the cfg file exitst, otherwise create a new file(does not work if the path is behind a directory that does not exist
	{
		this->file_content_ = new std::vector<std::string>;
		std::ifstream file(filePathAndName);

		std::string   temp_string;
		while (std::getline(file, temp_string))
		{
			if (temp_string.size() > 0)
				this->file_content_->push_back(temp_string); // read cfg file into vector full of strings
		}
	}
	else
	{
		file_content_ = new std::vector<std::string>;
		std::ofstream file{ filePathAndName };
		file.close();
	}
}

void pSettings::AddComment(const std::string& Key)
{
	if (!this->CheckExistanceOfKey(Key))
	{
		this->file_content_->push_back(Key);
	}
}

void pSettings::Save()
{
	this->DeleteAndSaveToFile();
	file_content_->clear();
	delete file_content_;
}

void pSettings::Clear()
{
	std::ofstream del;
	del.open(this->file_path_, std::ofstream::out | std::ofstream::trunc);
	del.close();
}

void pSettings::AddKeyAndValue(const std::string& Key, const std::string& Value)
{
	this->file_content_->push_back(Key + " = " + Value);
}

std::string pSettings::GetKeyByName(const std::string& Key)
{
	for (size_t i = 0; i < this->file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(Key) != std::string::npos)
			return (*file_content_)[i].substr((*file_content_)[i].find("=") + 1);
	}
	return "";
}

bool pSettings::CheckExistanceOfKey(const std::string& Key)
{
	for (size_t i = 0; i < this->file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(Key) != std::string::npos) {
			return true;
		}
	}
	return false;
}

void pSettings::ChangeKeyValue(const std::string& Key, const std::string& Value)
{
	for (size_t i = 0; i < this->file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(Key) != std::string::npos)
		{
			(*file_content_)[i].clear();
			(*file_content_)[i] = Key + " = " + Value;
		}
	}
}

void pSettings::DeleteAndSaveToFile()
{
	std::ofstream del;
	del.open(this->file_path_, std::ofstream::out | std::ofstream::trunc);
	del.close();

	std::ofstream file;
	file.open(this->file_path_);

	for (size_t i = 0; i < this->file_content_->size(); i++)
	{
		file << (*file_content_)[i] + "\n";
	}
	file.close();
}