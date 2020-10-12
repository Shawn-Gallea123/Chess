#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "../display/GraphicalDisplay.h"

void CheckShaderCompilation(const unsigned int shader) {
	int success;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		std::cerr << "Shader compilation failed: " << info_log << std::endl;
		exit(1);
	}
}

void CheckShaderProgramLink(const unsigned int shader_program) {
	int success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cerr << "Shader program linking failed: " << info_log << std::endl;
		exit(1);
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GraphicalDisplay* display = static_cast<GraphicalDisplay*>(glfwGetWindowUserPointer(window));
	if (!display) {
		std::cerr << "Cannot cast window user pointer to Display2D";
		exit(1);
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		display->SetShouldClose();
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void CursorPositionCallback(GLFWwindow* window, double x, double y) {
	GraphicalDisplay* display = static_cast<GraphicalDisplay*>(glfwGetWindowUserPointer(window));
	if (!display) {
		std::cerr << "Cannot cast window user pointer to Display2D";
		exit(1);
	}
	display->SetCursorPos(x, y);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	GraphicalDisplay* display = static_cast<GraphicalDisplay*>(glfwGetWindowUserPointer(window));
	if (!display) {
		std::cerr << "Cannot cast window user pointer to Display2D";
		exit(1);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		display->OnClick();
}

unsigned int CompileShader(const std::string& shader_path, int type) {
	std::ifstream file_text(shader_path);
	std::string shader_text((std::istreambuf_iterator<char>(file_text)),
		std::istreambuf_iterator<char>());
	unsigned int shader = glCreateShader(type);
	const char* shader_source = shader_text.c_str();
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	CheckShaderCompilation(shader);
	return shader;
}