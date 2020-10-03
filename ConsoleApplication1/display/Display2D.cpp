#include "Display2D.h"

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "../Board.h"

namespace {
	float tile_vertices[] = {
		// Top Left
		-0.125f, 0.125f, 0.0f,
		// Top Right
		0.125f, 0.125f, 0.0f,
		// Bottom right
		0.125f, -0.125f, 0.0f,
		// Bottom left
		-0.125f, -0.125f, 0.0f

	};

	unsigned int tile_indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	void CheckShaderCompilation(const unsigned int shader) {
		int success;
		char info_log[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, info_log);
			std::cout << "Shader compilation failed: " << info_log << std::endl;
			exit(1);
		}
	}

	void CheckShaderProgramLink(const unsigned int shader_program) {
		int success;
		char info_log[512];
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader_program, 512, NULL, info_log);
			std::cout << "Shader program linking failed: " << info_log << std::endl;
			exit(1);
		}
	}
}

Display2D::Display2D(Board* board) : GraphicalDisplay(board) {
	CompileShaders();
	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tile_vertices), tile_vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tile_indices), tile_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

bool Display2D::DrawBoard() {
	if (glfwWindowShouldClose(window_))
		return false;
	ProcessInput();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_program_);
	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window_);
	glfwPollEvents();
	return true;
}

void Display2D::CompileShaders() {
	// Vertex shader
	std::ifstream vertex_file_text("shaders/2DVectorShader.txt");
	std::string vertex_shader_text((std::istreambuf_iterator<char>(vertex_file_text)),
		std::istreambuf_iterator<char>());
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertex_shader_source = vertex_shader_text.c_str();
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	CheckShaderCompilation(vertex_shader);

	// Fragment shader
	std::ifstream fragment_file_text("shaders/2DFragmentShader.txt");
	std::string fragment_shader_text((std::istreambuf_iterator<char>(fragment_file_text)),
		std::istreambuf_iterator<char>());
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragment_shader_source = fragment_shader_text.c_str();
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	CheckShaderCompilation(fragment_shader);

	// Shader program
	shader_program_ = glCreateProgram();
	glAttachShader(shader_program_, vertex_shader);
	glAttachShader(shader_program_, fragment_shader);
	glLinkProgram(shader_program_);
	CheckShaderProgramLink(shader_program_);
	glUseProgram(shader_program_);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Display2D::ProcessInput() {
	if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window_, true);
	else if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}