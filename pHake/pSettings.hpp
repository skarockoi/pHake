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
	std::vector<std::string>* file_content_;
	std::string file_path_;
public:
	pSettings() {}
	pSettings(const std::string filePathAndName);

	template <typename T>
	T				AddGet(std::string Key, T Value);
	void			AddComment(std::string Key);

	template <typename T>
	bool			Edit(std::string Key, T Value);

	void			Save(); // save current state of "fileContent" to file
	void			Clear(); // clear "fileContent"

private:
	void			AddKeyAndValue(std::string Key, std::string Value);
	std::string		GetKeyByName(std::string Key);
	bool			CheckExistanceOfKey(std::string Key);
	void			ChangeKeyValue(std::string Key, std::string Value);
	void			DeleteAndSaveToFile();

	template <typename T>
	T LexicalCast(const std::string& str);
};


// public functions
pSettings::pSettings(const std::string filePathAndName)
{
	file_path_ = filePathAndName;

	if (std::filesystem::exists(filePathAndName)) // check if the cfg file exitst, otherwise create a new file(does not work if the path is behind a directory that does not exist
	{
		file_content_ = new std::vector<std::string>;
		std::ifstream file(filePathAndName);

		std::string   tempStr;
		while (std::getline(file, tempStr))
		{
			if (tempStr.size() > 0)
				file_content_->push_back(tempStr); // read cfg file into vector full of strings
		}

		for (size_t i = 0; i < file_content_->size(); i++)
		{
			(*file_content_)[i].erase(std::remove((*file_content_)[i].begin(), (*file_content_)[i].end(), '\n'), (*file_content_)[i].end()); // remove all "\n"s from strings
		}
	}
	else
	{
		file_content_ = new std::vector<std::string>;
		std::ofstream file{ filePathAndName };
		file.close();
	}
}

template<typename T>
inline T pSettings::AddGet(std::string Key, T Value)
{
	if (this->CheckExistanceOfKey(Key))
	{
		return this->LexicalCast<T>(this->GetKeyByName(Key));
	}
	else
	{
		this->AddKeyAndValue(Key, std::to_string(Value));
		return this->LexicalCast<T>(this->GetKeyByName(Key));
	}

	return 0;
}

void pSettings::AddComment(std::string Key)
{
	if (!this->CheckExistanceOfKey(Key))
	{
		this->file_content_->push_back(Key);
	}
}


template<typename T>
inline bool pSettings::Edit(std::string Key, T Value)
{
	if (this->CheckExistanceOfKey(Key))
	{
		this->ChangeKeyValue(Key, std::to_string(Value));
		return true;
	}
	return false;
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

// private functions
void pSettings::AddKeyAndValue(std::string Key, std::string Value)
{
	this->file_content_->push_back(Key + " = " + Value);
}

std::string pSettings::GetKeyByName(std::string Key)
{
	for (size_t i = 0; i < this->file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(Key) != std::string::npos)
			return (*file_content_)[i].substr((*file_content_)[i].find("=") + 1);

	}
	return "";
}

bool pSettings::CheckExistanceOfKey(std::string Key)
{
	for (size_t i = 0; i < this->file_content_->size(); i++)
	{
		if ((*file_content_)[i].find(Key) != std::string::npos) {
			return true;
		}
	}
	return false;
}
void pSettings::ChangeKeyValue(std::string Key, std::string Value)
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

template<typename T>
inline T pSettings::LexicalCast(const std::string& str)
{
	T var;
	std::istringstream iss;
	iss.str(str);
	iss >> var;
	return var;
}
#endif