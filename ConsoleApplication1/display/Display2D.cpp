#include "Display2D.h"

#include <chrono>
#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <streambuf>
#include <string>
#include <thread>

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

	const int framerate = 15;

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
	unsigned int model_trans_location = glGetUniformLocation(shader_program_, "M");
	int tile_color_location = glGetUniformLocation(shader_program_, "TileColor");
	auto selected_tile = board_->GetSelectedTile();
	int use_texture_location = glGetUniformLocation(shader_program_, "UseTexture");

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece* piece = board_->GetPiece(j, i);

			// Set tile colour.
			glUniformMatrix4fv(model_trans_location, 1, GL_FALSE, glm::value_ptr(M));
			if (selected_tile && selected_tile->first == j && selected_tile->second == i) {
				// Colour selected tile green.
				glUniform3f(tile_color_location, 0.0f, 1.0f, 0.0f);
			}
			else if (selected_tile && IsAMovementSpot(j, i, false)) {
				// Colour movement spot
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
				// Regular tile colour
				glUniform3f(tile_color_location, white_tile, white_tile, white_tile);
			}

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
				// TODO, make 0.25f constant, give it a name.
				start = glm::translate(start, glm::vec3(0.0f, 0.25f, 0.0f));
				M = start;
			}
			else {
				white_tile = !white_tile;
				M = glm::translate(M, glm::vec3(0.25f, 0.0f, 0.0f));
			}
		}
	}

	if (moving_piece_) {
		glUniform1i(use_texture_location, true);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, moving_piece_->GetTexture());
		glUniformMatrix4fv(model_trans_location, 1, GL_FALSE, glm::value_ptr(animating_mat_));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		animating_frames_--;
		std::cout << "Animating frames: " << animating_frames_ << std::endl;
		if (animating_frames_ < 0) {
			animating_ = false;
			board_->SetPiece(moving_piece_, new_x_, new_y_);
			moving_piece_ = nullptr;
		}
		else {
			animating_mat_ = glm::translate(animating_mat_, glm::vec3(x_interval_, y_interval_, 0.0f));
		}
	}

	glfwSwapBuffers(window_);
	if (animating_) {
		//std::this_thread::sleep_for(std::chrono::milliseconds(17));
		glfwPollEvents();
	}
	else {
		glfwWaitEvents();
	}
	return true;
}

void Display2D::CompileShaders() {
	unsigned int vertex_shader = CompileShader("shaders/2DVectorShader.txt", GL_VERTEX_SHADER);
	unsigned int fragment_shader = CompileShader("shaders/2DFragmentShader.txt", GL_FRAGMENT_SHADER);
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
	if (animating_)
		return;
	auto selected_tile = board_->GetSelectedTile();
	int original_x = 0;
	int original_y = 0;
	if (selected_tile) {
		original_x = selected_tile->first;
		original_y = selected_tile->second;
	}
	int tile_width = window_width_ / 8;
	int tile_height = window_height_ / 8;
	new_x_ = static_cast<int>(cursor_x_ / tile_width);
	new_y_ = 7 - static_cast<int>((cursor_y_ / tile_height));

	bool was_piece_moved = board_->OnClick(new_x_, new_y_);
	animating_ = was_piece_moved;
	if (was_piece_moved) {
		animating_frames_ = framerate;
		moving_piece_ = board_->PullPiece(new_x_, new_y_);
		animating_mat_ = glm::mat4(1.0f);
		animating_mat_ = glm::translate(animating_mat_, glm::vec3(-0.875f, -0.875f, 0.0f));
		// Set matrix to be at original spot, <orig_x, orig_y>
		animating_mat_ = glm::translate(animating_mat_, glm::vec3(original_x * 0.25f, original_y * 0.25f, 0.0f));
		// Get distance to new spot, divide by 60, store x and y intervals (60 fps must be added)
		float x_distance = (new_x_ - original_x) * 0.25f;
		float y_distance = (new_y_ - original_y) * 0.25f;
		x_interval_ = x_distance / framerate;
		y_interval_ = y_distance / framerate;
	}
}

bool Display2D::IsAMovementSpot(int x, int y, bool attacking) {
	auto selected_tile = board_->GetSelectedTile();
	auto spots = board_->GetPiece(selected_tile->first, selected_tile->second)->GetPossibleMovementSpots(board_, attacking);

	for (auto location : spots)
		if (location.first == x && location.second == y)
			return true;

	return false;
}