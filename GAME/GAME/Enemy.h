#pragma once
#include "func.h"
class Enemy :public Hero
{
public:
	static const int ENEMY_WIDTH =48;
	static const int ENEMY_HEIGHT = 84;
	//static const
	int ENEMY_VEL = -1;
	Enemy();
	void render(SDL_Rect& camera, SDL_RendererFlip &_flipType);
	void move(Tile* tiles[]);
	SDL_Rect mBox;
	double mVelX, mVelY;
	void setBox(int a, int b);
	SDL_Rect getBox();
	double direction = 1;
	void Enemy::flip(SDL_RendererFlip &_flipType);
};
void Enemy::setBox(int a, int b)
{
	mBox.x = a;
	mBox.y = b;
	
}
Enemy::Enemy()
{
	mBox.x = 980;
	mBox.y = 380;
	mBox.w = ENEMY_WIDTH;
	mBox.h = ENEMY_HEIGHT;
	mVelX = 0;
	mVelY = 0;
}
void Enemy::move(Tile* tiles[])
{

	//for (int i = 0; i < TOTAL_TILES; i++)
	//{
	//	//std::cout << mBox.w << std::endl;
	//	if (checkCollision(mBox,tiles[i]->getBox() ))
	//	{
	//		if (tiles[i]->getType() == TILE_BRICK)
	//		{
	//			std::cout << i << std::endl;
	//			ENEMY_VEL = -ENEMY_VEL;
	//		}
	//		else
	//		{
	//			break;
	//		}

	//	}
	//	
	//}
if (touchesWall1(mBox, tiles))
		{
			ENEMY_VEL = -ENEMY_VEL;
		}
	mBox.x += ENEMY_VEL;

	if (ENEMY_VEL < 0)
	{
		direction = -1;
	}
	if (ENEMY_VEL > 0)
	{
		direction = 1;
	}


}
SDL_Rect Enemy::getBox()
{
	return mBox;
}
void Enemy::flip(SDL_RendererFlip &_flipType)
{
	if (direction == 1)
	{
		_flipType = SDL_FLIP_NONE;
	}
	if (direction == -1)
	{
		_flipType = SDL_FLIP_HORIZONTAL;
	}
}

