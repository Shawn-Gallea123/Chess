#include <iostream>
#include <memory>

#include "Chess.h"

int main()
{
	std::unique_ptr<Chess> chess = std::make_unique<Chess>();
	chess->Run();
}