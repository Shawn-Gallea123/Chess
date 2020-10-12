#include <iostream>
#include <memory>

#include "Chess.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int main()
{
	stbi_set_flip_vertically_on_load(true);
	std::unique_ptr<Chess> chess = std::make_unique<Chess>();
	chess->Run();
}