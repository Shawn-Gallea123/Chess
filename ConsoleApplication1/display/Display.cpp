#include "Display.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {

// Resize viewport when window size changes.
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

}

Display::Display(Board* board) : board_(board) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: Fullscreen support
	window_ = glfwCreateWindow(800, 600, "Chess", NULL, NULL);
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
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
}

Display::~Display() {
	glfwTerminate();
}

