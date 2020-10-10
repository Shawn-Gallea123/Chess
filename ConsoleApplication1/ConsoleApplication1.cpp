#include <iostream>
#include <memory>

#include "Chess.h"

#define STB_IMAGE_IMPLEMENTATION

int main()
{
	std::unique_ptr<Chess> chess = std::make_unique<Chess>();
	chess->Run();
}