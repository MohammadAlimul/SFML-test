#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Arm : public sf::Drawable
{
public:
	sf::Vector2f pos;
	sf::Vector2f endPos;
	float length;
	float angle;
	sf::VertexArray arm;

	void initVariables()
	{
		this->arm.setPrimitiveType(sf::Lines);
		this->arm.resize(2);
		this->endPos.x = this->pos.x + std::cos(this->angle) * this->length;
		this->endPos.y = this->pos.y + std::sin(this->angle) * this->length;
		this->arm[0].position = this->pos;
		this->arm[1].position = this->endPos;
		//this->m_base = nullptr;

	}

	Arm()
	{

	}

	Arm(sf::Vector2f pos, float length, float angle)
	{
		this->pos = pos;
		this->length = length;
		this->angle = angle;
		//this->base = nullptr;

		this->initVariables();
	}

	Arm(sf::Vector2f pos, float length, float angle, Arm& base)
	{
		this->pos = pos;
		this->length = length;
		this->angle = angle;
		//this->base = new Arm();
		//this->base = &base;

		std::cout << "iyah\n";

		this->initVariables();
	}

	~Arm()
	{
		//delete base;
	}

	void setbase(Arm& base)
	{
		//this->base = &base;
	}

	void update(sf::Vector2f newPos, float angle, float baseAngle = 0)
	{
		if (this->pos != newPos)
			this->pos = newPos;

		this->angle = angle;

		this->endPos.x = this->pos.x + std::cos(this->angle + baseAngle) * this->length;
		this->endPos.y = this->pos.y + std::sin(this->angle + baseAngle) * this->length;
		this->arm[0].position = this->pos;
		this->arm[1].position = this->endPos;
	}

	sf::Vector2f GetEndPos()
	{
		//this->endPos.x = this->pos.x + std::cos(this->angle) * this->length;
		//this->endPos.y = this->pos.y + std::sin(this->angle) * this->length;

		return this->endPos;
	}

	float getAngle()
	{
		return this->angle;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(this->arm);
	}
};

