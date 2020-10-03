#pragma once

#include "Display.h"

class TextDisplay : public Display {
public:
	bool DrawBoard() override;

private:
	using Display::Display;
};