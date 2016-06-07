#pragma once
#include"func.h"

class Castle
{
public:
	static const int CASTLE_WIDTH = 24;
	static const int CASTLE_HEIGHT = 24;
	Castle();
	void render(SDL_Rect& camera);
	SDL_Rect getBox();
	SDL_Rect mBox;
	void setBox(int a, int b);


};
Castle::Castle()
{
	mBox.x = 100;
	mBox.y = 100;
	mBox.w = CASTLE_WIDTH;
	mBox.h = CASTLE_HEIGHT;
}
void Castle::setBox(int a, int b)
{
	mBox.x = a;
	mBox.y = b;
}
SDL_Rect Castle::getBox()
{
	return mBox;
}
