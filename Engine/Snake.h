#pragma once

#include "Location.h"
#include "Graphics.h"
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void Draw(Board& brd);
		void MoveBy(const Location& loc);
		Location GetLocation();
	private:
		Location loc;
		Color c;
	};
public:
	Snake( const Location& in_loc);
	void MoveBy(const Location& in_loc);
	Location GetNextHeadLocation(const Location& delta_loc);
	void GrowAndMoveBy(const Location& in_loc);
	void Draw(Board& brd);
	bool IsTileExceptEnd(const Location& target);
	bool IsTile(const Location& target);
private:
	static constexpr Color headColor = Colors::Gray;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	Location loc;
};
