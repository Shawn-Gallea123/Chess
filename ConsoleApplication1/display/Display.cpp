#include "Display.h"

#include <GLFW/glfw3.h>

Display::Display() {}

Display::~Display() {}

void Display::SetBoard(Board* board) {
	board_ = board;
}