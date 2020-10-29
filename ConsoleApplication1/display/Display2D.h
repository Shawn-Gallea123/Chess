#pragma once

#include "GraphicalDisplay.h"

#include <glm/glm.hpp>

class Board;
class Piece;

class Display2D : public GraphicalDisplay {
public:
	Display2D();

	bool DrawBoard() override;
	void OnClick() override;
	void OnPieceMoved(int x, int y, int dest_x, int dest_y) override;

private:
	void CompileShaders();
	bool IsAMovementSpot(int x, int y, bool attacking);

	unsigned int VAO_;
	unsigned int shader_program_;
	bool animating_ = false;
	int animating_frames_ = 0;
	glm::mat4 animating_mat_;
	Piece* moving_piece_ = nullptr;
	float x_interval_ = 0.0f;
	float y_interval_ = 0.0f;
	double last_time_ = 0.0;

	// Temp variables to hold destination until animating is complete.
	int new_x_ = 0;
	int new_y_ = 0;

};