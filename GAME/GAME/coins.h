#pragma once

#include"func.h"

class Coin
{
	public:
	static const int COIN_WIDTH = 24;
	static const int COIN_HEIGHT = 24;
	Coin();
	void render(SDL_Rect& camera, SDL_Rect* currentClip);
	SDL_Rect getBox();
	SDL_Rect mBox;
	void animation(int &_frame, const int &_COIN_ANIMATION_FRAMES);
	void setBox(int a, int b);
	
	
};
Coin::Coin()
{
	mBox.x =100;
	mBox.y = 100;
	mBox.w = COIN_WIDTH;
	mBox.h = COIN_HEIGHT;
}
void Coin::setBox(int a, int b)
{
	mBox.x = a;
	mBox.y = b;
}
void Coin::animation(int &_frame, const int &_COIN_ANIMATION_FRAMES)
{
	
		_frame++;
		if (_frame / 61 >= _COIN_ANIMATION_FRAMES)
		{
			_frame = 0;
		}

	
}
SDL_Rect Coin::getBox()
{
	return mBox;
}

