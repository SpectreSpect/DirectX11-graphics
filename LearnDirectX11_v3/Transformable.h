#pragma once
#include "mymath.h"
#include "Transform.h"

class Transformable
{
public:
	float3 position = {};
	float3 rotation = {};
	float3 scale = { 1, 1, 1 };
	//Transform transfrom;
};
