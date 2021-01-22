#include "pSettings.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>

pSettings::pSettings()
{
	this->file_content_ = new std::vector<std::string>;
}

pSettings::~pSettings()
{
	delete[] this->file_content_;
}

bool pSettings::Open(const std::string& Filepath)
{
	this->file_path_ = Filepath;

	if (std::filesystem::exists(Filepath))
	{
		std::ifstream file(Filepath);

		std::string   temp_string;
		while (std::getline(file, temp_string))
		{
			if (temp_string.size() > 0)
				this->file_content_->push_back(temp_string);
		}
		return 1;
	}
	else
	{
		std::ofstream file{ Filepath };
		file.close();
		return 0;
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
	std::ofstream del;
	del.open(this->file_path_, std::ofstream::out | std::ofstream::trunc);
	del.close();

	std::ofstream file;
	file.open(this->file_path_);

	for (size_t i = 0; i < this->file_content_->size(); i++)
		file << (*this->file_content_)[i] + "\n";
	
	file.close();
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