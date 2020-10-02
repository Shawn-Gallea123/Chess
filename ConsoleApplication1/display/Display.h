#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Board;

class Display {
public:
	Display(Board* board);
	virtual ~Display();

	virtual void DrawBoard() = 0;

protected:
	Board* board_;

	GLFWwindow* window_;
};