#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Display.h"

class Board;

class GraphicalDisplay : public Display {
public:
	GraphicalDisplay();
	~GraphicalDisplay() override;

	void SetShouldClose();
	void SetCursorPos(double x, double y);
	void SetWindowSize(int width, int height);
	virtual void OnClick() = 0;

protected:
	GLFWwindow* window_;
	int window_width_ = 800;
	int window_height_ = 800;
	double cursor_x_ = 0;
	double cursor_y_ = 0;
};