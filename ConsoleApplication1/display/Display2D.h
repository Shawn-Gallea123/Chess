#pragma once

#include "GraphicalDisplay.h"

class Board;

class Display2D : public GraphicalDisplay {
public:
	Display2D();
	bool DrawBoard() override;

private:
	using GraphicalDisplay::GraphicalDisplay;

	void CompileShaders();
	void ProcessInput();

	unsigned int VAO_;
	unsigned int shader_program_;

};