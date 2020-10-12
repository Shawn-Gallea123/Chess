#include "Display2D.h"

#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <streambuf>
#include <string>

#include "../Board.h"
#include "../util/GraphicsUtils.h"

namespace {

	float tile_vertices[] = {
		// Top Left        // Texture coords
		-0.125f, 0.125f, 0.0f, 0.0f, 1.0f,
		// Top Right
		0.125f, 0.125f, 0.0f, 1.0f, 1.0f,
		// Bottom right
		0.125f, -0.125f, 0.0f, 1.0f, 0.0f,
		// Bottom left
		-0.125f, -0.125f, 0.0f, 0.0f, 0.0f
	};

	unsigned int tile_indices[] = {
		0, 1, 2,
		0, 2, 3
	};

}

Display2D::Display2D() {
	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, KeyCallback);
	glfwSetCursorPosCallback(window_, CursorPositionCallback);
	glfwSetMouseButtonCallback(window_, MouseButtonCallback);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

bool Display2D::DrawBoard() {
	if (glfwWindowShouldClose(window_))
		return false;
	else if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_program_);

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(-0.875f, -0.875f, 0.0f));

	glm::mat4 start = M;
	bool white_tile = false;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board_->GetPiece(j, i);

			// Set tile colour.
			unsigned int model_trans_location = glGetUniformLocation(shader_program_, "M");
			int tile_color_location = glGetUniformLocation(shader_program_, "TileColor");
			auto selected_tile = board_->GetSelectedTile();
			if (selected_tile && selected_tile->first == j && selected_tile->second == i) {
				glUniformMatrix4fv(model_trans_location, 1, GL_FALSE, glm::value_ptr(M));
				glUniform3f(tile_color_location, 0.0f, 1.0f, 0.0f);
			}
			else if (selected_tile && IsAMovementSpot(j, i, false)) {
				glUniformMatrix4fv(model_trans_location, 1, GL_FALSE, glm::value_ptr(M));
				float colour;
				if (white_tile) {
					if (IsAMovementSpot(j, i, true) && piece)
						glUniform3f(tile_color_location, 1.0f, 0.47f, 0.47f);
					else
						glUniform3f(tile_color_location, 0.47f, 1.0f, 0.53f);
				}
				else {
					if (IsAMovementSpot(j, i, true) && piece)
						glUniform3f(tile_color_location, 0.3f, 0.0f, 0.0f);
					else
						glUniform3f(tile_color_location, 0.0f, 0.3f, 0.0f);
				}
			}
			else {
				glUniformMatrix4fv(model_trans_location, 1, GL_FALSE, glm::value_ptr(M));
				glUniform3f(tile_color_location, white_tile, white_tile, white_tile);
			}

			int use_texture_location = glGetUniformLocation(shader_program_, "UseTexture");
			glBindVertexArray(VAO_);

			// Draw tile
			glUniform1i(use_texture_location, false);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// Draw piece
			if (piece) {
				glUniform1i(use_texture_location, true);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, piece->GetTexture());
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}

			if (j == 7) {
				start = glm::translate(start, glm::vec3(0.0f, 0.25f, 0.0f));
				M = start;
			}
			else {
				white_tile = !white_tile;
				M = glm::translate(M, glm::vec3(0.25f, 0.0f, 0.0f));
			}
		}
	}

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

void Display2D::OnClick() {
	int tile_width = window_width_ / 8;
	int tile_height = window_height_ / 8;
	int tile_x = cursor_x_ / tile_width;
	int tile_y = 7 - static_cast<int>((cursor_y_ / tile_height));
	board_->OnClick(tile_x, tile_y);
}

bool Display2D::IsAMovementSpot(int x, int y, bool attacking) {
	auto selected_tile = board_->GetSelectedTile();
	auto spots = board_->GetPiece(selected_tile->first, selected_tile->second)->GetPossibleMovementSpots(board_, attacking);

	for (auto location : spots)
		if (location.first == x && location.second == y)
			return true;

	return false;
}