#pragma once

#include "GraphicalDisplay.h"

class Board;

class Display2D : public GraphicalDisplay {
public:
	void DrawBoard() override;

private:
	using GraphicalDisplay::GraphicalDisplay;
};