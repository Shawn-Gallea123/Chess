#include "Display2D.h"

#include "../Board.h"

void Display2D::DrawBoard() {
	glfwSwapBuffers(window_);
	glfwPollEvents();
}