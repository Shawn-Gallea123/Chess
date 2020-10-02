#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"

class Board;

class GraphicalDisplay : public Display {
public:
	GraphicalDisplay(Board* board);
	~GraphicalDisplay() override;

protected:
	GLFWwindow* window_;
};