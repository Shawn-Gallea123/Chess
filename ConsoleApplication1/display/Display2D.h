#pragma once

#include "GraphicalDisplay.h"

class Board;

class Display2D : public GraphicalDisplay {
public:
	Display2D(Board* board);
	bool DrawBoard() override;

private:
	using GraphicalDisplay::GraphicalDisplay;

	void CompileShaders();

	unsigned int VAO_;
	unsigned int shader_program_;

};