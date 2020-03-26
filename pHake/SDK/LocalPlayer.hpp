#ifndef _LOCALPLAYER_HPP_
#define _LOCALPLAYER_HPP_

#include "../Memory/Process.h"

class LocalPlayer : public DataWrapper<0x14BC + 0x4>
{
public:
	LocalPlayer() {}
	LocalPlayer(HANDLE& h)
	{
		this->handle = &h;
		this->classStart = 0x0;
	}

	bool freezeMomentum()
	{
		if (this->read<uint8_t>(0x2E) == 2)
		{
			return true;
		}
		else
		{
			return true;
		}
	}

	void freezeMomentum(bool value)
	{
		if (value)
		{
			this->write<uint8_t>(0x2E, 2);
		}
		else
		{
			this->write<uint8_t>(0x2E, 1);
		}
	}

	uint64_t position = 0x30;

	bool god()
	{
		return this->read<bool>(0x189);
	}

	void god(bool value)
	{
		this->write<bool>(0x189, value);
	}

	float health()
	{
		return this->read<float>(0x280);
	}

	void health(float value)
	{
		this->write<float>(0x280, value);
	}

	float healthMax()
	{
		return this->read<float>(0x2A0);
	}

	void healthMax(float value)
	{
		this->write<float>(0x2A0, value);
	}

	vector3 speedXYZ()
	{
		this->read<vector3>(0x320);
	}

	void speedXYZ(vector3 value)
	{
		this->write<vector3>(0x320, value);
	}

	void speedXYZ(float x, float y, float z)
	{
		vector3 value;
		value.x = x;
		value.y = y;
		value.z = z;

		this->write<vector3>(0x320, value);
	}

	float speedX()
	{
		return this->read<float>(0x320);
	}

	void speedX(float value)
	{
		this->write<float>(0x320, value);
	}

	float speedY()
	{
		return this->read<float>(0x324);
	}

	void speedY(float value)
	{
		this->write<float>(0x324, value);
	}

	float speedZ()
	{
		return this->read<float>(0x328);
	}

	void speedZ(float value)
	{
		this->write<float>(0x328, value);
	}

	uint64_t vehicle = 0xD28;

	int32_t inVehicle()
	{
		if (this->read<int32_t>(0xE44) != 0)
			return true;
		else
			return false;
	}

	bool ragdoll()
	{
		if (!this->read<unsigned char>(0x10A8) == 1)
			return false;
		else
			return true;
	}

	void ragdoll(bool value)
	{
		if (value)
			this->write<unsigned char>(0x10A8, 1);
		else
			this->write<unsigned char>(0x10A8, 32);	
	}

	uint64_t playerInfo = 0x10B8;

	float armor()
	{
		return this->read<float>(0x14B8);
	}

	void armor(float value)
	{
		this->write<float>(0x14B8, value);
	}
};
#endif