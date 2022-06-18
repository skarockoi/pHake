#include "pINI.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>

pINI::pINI()
{
	file_content_ = new std::vector<std::string>;
}

pINI::~pINI()
{
	delete[] file_content_;
}

bool pINI::Open(const std::string& filepath)
{
	file_path_ = filepath;

	if (std::filesystem::exists(filepath))
	{
		std::ifstream file(filepath);

		std::string   temp_string;
		while (std::getline(file, temp_string))
		{
			if (temp_string.size() > 0)
				file_content_->push_back(temp_string);
		}
		return 1;
	}
	else
	{
		std::ofstream file{ filepath };
		file.close();
		return 0;
	}
}

void pINI::Comment(const std::string& key)
{
	if (!CheckExistanceOfKey(key))
	{
		file_content_->push_back(key);
	}
}

void pINI::Save()
{
	std::ofstream del;
	del.open(file_path_, std::ofstream::out | std::ofstream::trunc);
	del.close();

	std::ofstream file;
	file.open(file_path_);

	for (size_t i = 0; i < file_content_->size(); i++)
		file << (*file_content_)[i] + "\n";
	
	file.close();
}

void pINI::Clear()
{
	std::ofstream del;
	del.open(file_path_, std::ofstream::out | std::ofstream::trunc);
	del.close();
}

void pINI::AddKeyAndValue(const std::string& key, const std::string& value)
{
	file_content_->push_back(key + "=" + value);
}

std::string pINI::GetKeyByName(const std::string& key)
{
	for (size_t i = 0; i < file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(key) != std::string::npos)
			return (*file_content_)[i].substr((*file_content_)[i].find("=") + 1);
	}
	return "";
}

bool pINI::CheckExistanceOfKey(const std::string& key)
{
	for (size_t i = 0; i < file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(key+"=") != std::string::npos) {
			return true;
		}
	}
	return false;
}

void pINI::ChangeKeyValue(const std::string& key, const std::string& value)
{
	for (size_t i = 0; i < file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(key+"=") != std::string::npos)
		{
			(*file_content_)[i].clear();
			(*file_content_)[i] = key+ "=" + value;
		}
	}
}