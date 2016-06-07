#pragma once
#include"func.h"

class Cloud
{
public:
	static const int CLOUD_WIDTH = 24;
	static const int CLOUD_HEIGHT = 24;
	Cloud();
	void render(SDL_Rect& camera);
	SDL_Rect getBox();
	SDL_Rect mBox;
	void setBox(int a, int b);


};
Cloud::Cloud()
{
	mBox.x = 100;
	mBox.y = 100;
	mBox.w = CLOUD_WIDTH;
	mBox.h = CLOUD_HEIGHT;
}
void Cloud::setBox(int a, int b)
{
	mBox.x = a;
	mBox.y = b;
}
SDL_Rect Cloud::getBox()
{
	return mBox;
}
