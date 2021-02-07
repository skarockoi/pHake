#ifndef _PITEM_HPP_
#define _PITEM_HPP_

#include <SFML/Graphics.hpp>

class pItemBone
{
public:
	void Create(sf::RenderWindow* const& Window, sf::Font* Font);
	void Draw();
	virtual void Loop() = 0;

public:
	void		 position(uint32_t x, uint32_t y);
	void		 size(uint32_t x, uint32_t y);
	bool		 IsOnBox();
	sf::Vector2f size();

protected:
	void	 Hightlight(bool value);

protected:
	uint16_t sleep_duration_ = 0;
	bool	 resizeable_ = false;
	bool	 active_ = false;
	bool     busy_ = false;

	sf::RenderWindow*  window_;
	sf::Font*		   font_;

	sf::Text		   text_;
	sf::RectangleShape rect_back_;
};
#endif


#ifndef _PITEMTYPES_HPP_
#define _PITEMTYPES_HPP_

class pItemInt : public pItemBone
{
private:
	uint32_t* value_;
	uint32_t inc_;
	uint32_t dec_;
public:
	void AddValue(uint32_t& Value, uint32_t Inc, uint32_t Dec);
	void Loop();
};


class pItemFloat : public pItemBone
{
public:
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