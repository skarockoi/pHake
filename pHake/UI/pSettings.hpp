#ifndef _PSETTINGS_HPP_
#define _PSETTINGS_HPP_

#include <string>
#include <vector>

class pSettings
{
private:
	std::vector<std::string>* file_content_;
	std::string file_path_;
public:
	pSettings();
	~pSettings();
	
	bool			Open(const std::string& Filepath);
	template <typename T>
	T				AddGet(const std::string& Key, T Value);
	void			AddComment(const std::string& Key);

	template <typename T>
	bool			Edit(const std::string& Key, T Value);
	void			Save();
	void			Clear();

private:
	void			AddKeyAndValue(const std::string& Key, const std::string& Value);
	std::string		GetKeyByName(const std::string& Key);
	bool			CheckExistanceOfKey(const std::string& Key);
	void			ChangeKeyValue(const std::string& Key, const std::string& Value);

	template <typename T>
	T LexicalCast(const std::string& str);
};
#endif

template<typename T>
inline T pSettings::AddGet(const std::string& Key, T Value)
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

template<typename T>
inline bool pSettings::Edit(const std::string& Key, T Value)
{
	if (this->CheckExistanceOfKey(Key))
	{
		this->ChangeKeyValue(Key, std::to_string(Value));
		return true;
	}
	return false;
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