#ifndef _PITEM_HPP_
#define _PITEM_HPP_

#include <SFML/Graphics.hpp>

class pItemBone
{
public:
	pItemBone();
	void Create(sf::RenderWindow* const& Window, sf::Font* Font);
	void Draw();
	virtual void Loop() = 0;

public:
	void		 position(sf::Vector2f xy);
	void		 size(sf::Vector2f xy);
	bool		 IsOnBox();
	sf::Vector2f size();

protected:
	void	 Hightlight(bool value);

protected:
	sf::RenderWindow*  window_;
	sf::Font*		   font_;

	sf::Text		   text_;
	sf::RectangleShape rect_back_;

	uint16_t sleep_duration_;
	bool	 resizeable_;
	bool	 active_;
	bool     busy_;
};
#endif


#ifndef _PITEMTYPES_HPP_
#define _PITEMTYPES_HPP_

class pItemInt : public pItemBone
{
public:
	pItemInt() : value_(0), inc_(0), dec_(0) { }
	void AddValue(uint32_t& Value, uint32_t Inc, uint32_t Dec);
	void Loop();

private:
	uint32_t* value_;
	uint32_t inc_;
	uint32_t dec_;
};


class pItemFloat : public pItemBone
{
public:
	pItemFloat() : value_(0), inc_(0.f), dec_(0.f) { }
	void AddValue(float& Value, float Inc, float Dec);
	void Loop();

private:
	float* value_;
	float inc_;
	float dec_;
};


class pItemBool : public pItemBone
{
public:
	pItemBool() : value_(0) { }
	void AddValue(bool& Value);
	void Loop();

private:
	bool* value_;
};


class pItemString : public pItemBone
{
public:
	void AddValue(const std::string Value);
	void Loop();

private:
	std::string value_;
};
#endif