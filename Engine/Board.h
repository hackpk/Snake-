#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	enum class Contents
	{
		Empty,
		Obstacle,
		Food,
		Poison
	};
public:
	Board(Graphics& gfx);
	void DrawCell( Location& in_loc,Color c);
	int GetWidth();
	int GetHeight();
	bool IsInsideBoard(const Location& inside);
	void DrawBorder();
	Contents GetContents(const Location& loc);
	void ConsumeContents(const Location& in_loc);
	void SpawnContents(std::mt19937 & rng, class Snake& snake,Contents contentLayer);
	void DrawCells();
private:
	static constexpr Color obstacleColor = Colors::White;
	static constexpr Color poisonColor = Colors::Green;
	static constexpr Color foodColor = Colors::Red;
	static constexpr Color borderColor = Colors::Gray;
	static constexpr int dimension = 20;
	static constexpr int width = 25;
	static constexpr int height = 25;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	static constexpr int x = 31;
	static constexpr int y = 25;
	// 0: empty 1 : obstacle 2:food ,3::posion
	Contents hasContents[width * height] = {Contents::Empty};
	Graphics& gfx;
};
