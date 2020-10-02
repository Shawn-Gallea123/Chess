#pragma once

#include "Display.h"

class TextDisplay : public Display {
public:
	void DrawBoard() override;

private:
	using Display::Display;
};