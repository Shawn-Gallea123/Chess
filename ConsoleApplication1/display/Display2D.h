#pragma once

#include "GraphicalDisplay.h"

class Board;

class Display2D : public GraphicalDisplay {
public:
	Display2D();

	bool DrawBoard() override;
	void OnClick() override;

private:
	void CompileShaders();
	bool IsAMovementSpot(int x, int y);

	unsigned int VAO_;
	unsigned int shader_program_;

};