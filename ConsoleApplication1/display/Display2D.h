#pragma once

#include "Display.h"

class Board;

class Display2D : public Display {
public:
	void DrawBoard() override;

private:
	using Display::Display;
};