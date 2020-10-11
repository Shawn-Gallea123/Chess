#include "Piece.h"

#include <iostream>

#include "../Board.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <glad/glad.h>

Piece::Piece(int x, int y, Team team) 
	: x_(x), y_(y), team_(team) {}

Piece::~Piece() {}

Piece::Team Piece::GetTeam() {
	return team_;
}

void Piece::OnMoved(int x, int y) {
	x_ = x;
	y_ = y;
}

bool Piece::CheckSpace(int x, int y, std::vector<std::pair<int, int>>& spots, const Board* board) const {
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return false;
	Piece* piece = board->GetPiece(x, y);
	if (piece && piece->GetTeam() != team_) {
		spots.emplace_back(x, y);
		return false;
	}
	else if (!piece) {
		spots.emplace_back(x, y);
		return true;
	}
	else {
		return false;
	}
}

int Piece::GetX() {
	return x_;
}

int Piece::GetY() {
	return y_;
}

unsigned int Piece::Generate2DTexture(const std::string& path) {
	unsigned int texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		exit(1);
	}
	stbi_image_free(data);
	return texture;
}