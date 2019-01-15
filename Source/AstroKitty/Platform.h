#pragma once

#include <AstroKitty/SpatialObject.h>
#include <Core/Engine.h>

class Platform : public SpatialObject
{
public:
	enum PlatformType
	{
		PLATFORMTYPE_REFLECTION, PLATFORMTYPE_STATION, PLATFORMTYPE_FINISH
	};

	Platform(PlatformType type) : type(type) {};
	virtual ~Platform() {};

	virtual void Update(float deltaTimeSeconds) override {};

	PlatformType GetType() { return type; }
	void SetType(PlatformType type) { this->type = type; }

private:
	PlatformType type;
};