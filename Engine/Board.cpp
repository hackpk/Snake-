#include "Board.h"
#include "Snake.h"
#include  "assert.h"

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{
}


void Board::DrawCell( Location & in_loc, Color c)
{
	assert(in_loc.x >= 0);
	assert(in_loc.x <= width);
	assert(in_loc.y >= 0);
	assert(in_loc.y <= height);
	int off_x = x;
	int off_y = y;
	gfx.DrawRect(in_loc.x*dimension + off_x +cellPadding, in_loc.y*dimension + off_y + cellPadding, dimension - cellPadding *2, dimension -cellPadding *2, c);
}

int Board::GetWidth()
{
	return Board::width;
}

int Board::GetHeight()
{
	return Board::height;
}

bool Board::IsInsideBoard(const Location & inside)
{
	return inside.x >= 0 && inside.x <=width 
		&& inside.y >=0 && inside.y <=height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int right = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int bottom = left+ (borderWidth + borderPadding) * 2 + width * dimension;


	//top
	gfx.Draw(left,top,right,top+borderWidth,borderColor);

	//left
	gfx.Draw(left, top+borderWidth, left + borderWidth,bottom-borderWidth, borderColor);
	
	//right
	gfx.Draw(right-borderWidth,top+borderWidth,right,bottom-borderWidth,borderColor);

	//bottom
	gfx.Draw(left,bottom-borderWidth,right,bottom,borderColor);
}

void Board::ConsumeContents(const Location & in_loc)
{
	assert(GetContents(in_loc) == (Contents::Food) || GetContents(in_loc) == (Contents::Poison));
	hasContents[in_loc.y*width + in_loc.x] = Contents::Empty;
}

Board::Contents Board::GetContents(const Location & loc)
{
	return hasContents[loc.y*width+loc.x];
}

void Board::SpawnContents(std::mt19937 & rng, Snake & snake,Contents contentLayer)
{
	std::uniform_int_distribution<int> x_dist(0, GetWidth() - 1);
	std::uniform_int_distribution<int> y_dist(0, GetHeight() - 1);

	Location m_loc;
	do
	{
		m_loc.x = x_dist(rng);
		m_loc.y = y_dist(rng);
	} while (snake.IsTile(m_loc) || GetContents(m_loc) != Contents::Empty );
	hasContents[m_loc.y*width + m_loc.x] = contentLayer;
}

void Board::DrawCells()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Location loc = { x,y };
			const Contents contents = GetContents(loc);
			switch (contents)
			{
			case Contents::Obstacle:
				DrawCell(loc, obstacleColor);
				break;
			case Contents::Food:
				DrawCell(loc, foodColor);
				break;
			case Contents::Poison:
				DrawCell(loc, poisonColor);
				break;
			}
		}
	}
}




