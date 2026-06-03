#pragma once

#include <string>

namespace PetManager
{
	struct Toy
	{
		virtual ~Toy() = default;
		float apeal = 1.0f;
	};

	struct ToyBone : Toy
	{
		float durability = 5.0f;
	};

	struct ToyMouse : Toy
	{
		float durability = 1.5f;
	};
}


