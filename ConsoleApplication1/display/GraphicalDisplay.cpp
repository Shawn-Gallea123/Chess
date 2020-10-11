#include "GraphicalDisplay.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {

// Resize viewport when window size changes.
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	// User pointer is set in subclass.
	GraphicalDisplay* display = static_cast<GraphicalDisplay*>(glfwGetWindowUserPointer(window));
	if (!display) {
		std::cerr << "Cannot cast window user pointer to Display2D";
		exit(1);
	}
	display->SetWindowSize(width, height);
}

}

GraphicalDisplay::GraphicalDisplay() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: Fullscreen support
	window_ = glfwCreateWindow(window_width_, window_height_, "Chess", NULL, NULL);
	if (window_ == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}

	// TODO: Fullscreen support
	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
}

GraphicalDisplay::~GraphicalDisplay() {
	glfwTerminate();
}

void GraphicalDisplay::SetShouldClose() {
	glfwSetWindowShouldClose(window_, true);
}

void GraphicalDisplay::SetCursorPos(double x, double y) {
	cursor_x_ = x;
	cursor_y_ = y;
}

void GraphicalDisplay::SetWindowSize(int width, int height) {
	window_width_ = width;
	window_height_ = height;
}

