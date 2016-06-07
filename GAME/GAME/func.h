#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include<iostream>
#include<vector>
#include <sstream>

#include"Tiles.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 8000;
const int LEVEL_HEIGHT = 480;

const int TOTAL_TILES = 2400;
const int TOTAL_TILE_SPRITES = 3;

const int TILE_FLOOR = 0;
const int TILE_SKY = 1;
const int TILE_BRICK = 2;
Mix_Chunk *gCoin = NULL;
Mix_Music *gMusic = NULL;

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool touchesWall(SDL_Rect box, Tile* tiles[])
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() == TILE_FLOOR) || (tiles[i]->getType() == TILE_BRICK))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}
bool touchesWall1(SDL_Rect box, Tile* tiles[])
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() == TILE_BRICK))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}
bool checkCollisionX(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int centerA, leftB;
	int  rightB;
	

	//Calculate the sides of rect A
	centerA = a.x+(a.w/2);
	//rightA = a.x + a.w;
	

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;

	
	if (centerA <= leftB)
	{
		return false;
	}
	if (centerA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}