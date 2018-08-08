#include "Snake.h"
#include "assert.h"

Snake::Snake( const Location & in_loc)
{

	constexpr int nbodyColor = 4;
    constexpr Color bodycolors[nbodyColor] =
	{
		(10,100,65),
		(18,135,40),
		(12,125,55),
		(20,138,45)
	};
	for (int i = 0; i < nSegmentsMax; i++)
	{
		segments[i].InitBody(bodycolors[i % nbodyColor]);
	}
	segments[0].InitHead(in_loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i-1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc)
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::GrowAndMoveBy(const Location& in_loc)
{
	if (nSegments < nSegmentsMax)
	{
		nSegments++;
	}
	MoveBy(in_loc);
}

void Snake::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsTileExceptEnd(const Location & target)
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsTile(const Location & target)
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color in_c)
{
	c = in_c;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & brd)
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

Location Snake::Segment::GetLocation()
{
	return loc;
}
