#include "A2DEngine/Utils/DateTime.h"

#include <GLFW/glfw3.h>

namespace Aserai2D
{
	double DateTime::GetTimeSeconds()
	{
		return glfwGetTime();
	}

	double DateTime::GetTimeMilliSeconds()
	{
		return glfwGetTime() * 1000;
	}
}
