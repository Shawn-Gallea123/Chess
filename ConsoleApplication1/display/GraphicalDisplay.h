#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"

class Board;

class GraphicalDisplay : public Display {
public:
	GraphicalDisplay();
	~GraphicalDisplay() override;

protected:
	GLFWwindow* window_;
};