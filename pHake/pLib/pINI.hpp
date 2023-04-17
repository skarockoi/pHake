#ifndef _PINI_HPP_
#define _PINI_HPP_

#include <string>
#include <sstream>
#include <vector>

class pINI // INI Parser
{
public:
	pINI();
	~pINI();
	
	bool			Open(const std::string& filepath);
	template <typename T>
	T				Get(const std::string& key, T default_value);
	template <typename T>
	bool			Edit(const std::string& key, T value);

	void			Comment(const std::string& key);
	void			Save();
	void			Clear();

private:
	void			AddKeyAndValue(const std::string& key, const std::string& value);
	std::string		GetKeyByName(const std::string& key);
	bool			CheckExistanceOfKey(const std::string& key);
	bool			CheckExistanceOfComment(const std::string& comment);
	bool			ChangeKeyValue(const std::string& key, const std::string& value);
	bool			CreateDirectoryRecursive(const std::string& dirName);
	std::vector<std::string> split(const std::string& str, const char sep); // split a string separated by sep into a vector


	template <typename T>
	T LexicalCast(const std::string& str);

private:
	std::vector<std::string>* file_content_;
	std::string file_path_;
};

template<typename T>
inline T pINI::Get(const std::string& key, T value)
{
	if (this->CheckExistanceOfKey(key))
		return this->LexicalCast<T>(this->GetKeyByName(key));
	else
	{
		this->AddKeyAndValue(key, std::to_string(value));
		return this->LexicalCast<T>(this->GetKeyByName(key));
	}

	return 0;
}

template<typename T>
inline bool pINI::Edit(const std::string& key, T value)
{
	if (this->CheckExistanceOfKey(key))
	{
		this->ChangeKeyValue(key, std::to_string(value));
		return true;
	}
	return false;
}

template<typename T>
inline T pINI::LexicalCast(const std::string& str)
{
	T var{};
	std::istringstream iss;
	iss.str(str);
	iss >> var;
	return var;
}
#endif