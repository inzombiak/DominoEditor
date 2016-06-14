#pragma once

#include <array>
#include <vector>
#include "glm\glm.hpp"

class Object;
namespace GameDefs
{
	enum GameKey
	{
		W,
		A,
		S,
		D,
		Alt,
		Ctrl,
		Delete,
		Up,
		Down,
		Left,
		Right
	};

	struct RenderCompCreationData
	{
		Object* owner;

		int id;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> color;

		unsigned int drawType;
	};


}
