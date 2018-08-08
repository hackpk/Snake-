#pragma once

class Location {
public:

	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;

	}
	bool operator==(const Location& loc)
	{
		return x==loc.x&&y==loc.y;
	}
	
	int x;
	int y;
};
