#pragma once

#include"func.h"
#include"Tiles.h"

class Hero
{
public:
	//The dimensions of the dot
	static const int HERO_WIDTH = 55;
	static const int HERO_HEIGHT = 66;
	
	//Maximum axis velocity of the dot
	static const int HERO_VEL = 5;
	static const int JUMP_VEL = 23;
	//Initializes the variables
	Hero();
	void handleEvent(SDL_Event& e);
	//Moves the dot and check collision against tiles
	void move(Tile *tiles[]);
	void setY(double _y);
	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);
	bool type(Tile *tiles[]);
	//Shows the dot on the screen
	void render(SDL_Rect& camera, SDL_Rect* currentClip , SDL_RendererFlip &_flipType);
	SDL_Rect getBox();
	int getFrame();
	void setFrame(int a);
	int diference;
	void animation(int &_frame, const int &_WALKING_ANIMATION_FRAMES);
	void flip(SDL_RendererFlip &_flipType);
	//Non-Const variables
	bool isMoving = false;
	bool jump();
	double direction = 1;
	bool grounded = false;
	bool isJumping = false;
private:
	//Collision box of the dot
	SDL_Rect mBox;

	//The velocity of the dot
	double mVelX, mVelY;
	
};
Hero::Hero()
{
	//Initialize the collision box
	mBox.x = 0;
	mBox.y = 320;
	mBox.w = HERO_WIDTH;
	mBox.h = HERO_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}
bool Hero::jump()
{
	if (mBox.y <= 295)
	{
return true;
	}
			
		else
			return false;
	
}
void Hero::handleEvent(SDL_Event& e)
{
	
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			
			
		case SDLK_SPACE:
		{
			if (isJumping == false)
			{
			mVelY -= JUMP_VEL;
			diference = mBox.y;
			grounded=false;
			isJumping = true;
			}
			break;
		}
		case SDLK_a: mVelX -= HERO_VEL; isMoving = true; direction = -1;  break;
		case SDLK_d:mVelX += HERO_VEL; isMoving = true; direction = 1; break;
		
		}

		
	}
	
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			
		case SDLK_SPACE:
		{

			mVelY += JUMP_VEL;
			break;
			
		}
		case SDLK_a: mVelX += HERO_VEL; isMoving = false; break;
		case SDLK_d:mVelX -= HERO_VEL; isMoving = false; break;
		}
		
	}
	
	
}
bool Hero::type(Tile *tiles[])
{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() == TILE_BRICK))
		{
			return true;
		}
	}
	return false;
}
void Hero::animation(int &_frame, const int &_WALKING_ANIMATION_FRAMES)
{
	if (isMoving == true)
	{
		_frame++;
		if (_frame / 6 >= _WALKING_ANIMATION_FRAMES)
		{
		_frame = 0;
		}

	}
}
void Hero::move(Tile *tiles[])
{

	
	//Move the dot left or right
	mBox.x += mVelX;


	
	//If the dot went too far to the left or right or touched a wall
	if ((mBox.x < 0) || (mBox.x + HERO_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles))
	{

		//move back
		mBox.x -= mVelX;
	}



	//Move the dot up or down
	
	mBox.y += mVelY;
	
	//If the dot went too far up or down or touched a wall
	if ((mBox.y < 0) || (mBox.y + HERO_HEIGHT > LEVEL_HEIGHT)||(diference-mBox.y)>150)
	{
		
	
			//move back
			mBox.y -= mVelY;
		
	}
	if (touchesWall(mBox, tiles) == true)
	{
		mBox.y -= mVelY;
		grounded = true;
		mVelY = 0;
		isJumping = false;
		
	}
	if (isJumping==false)
		grounded = false;
	
	
	
	if (grounded==false)
	{
		mVelY += 7;
		grounded = true;
		
	
	}

}
void Hero::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (mBox.x + HERO_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + HERO_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}
SDL_Rect Hero::getBox()
{
	return mBox;
}
void Hero::setY(double _y)
{
	mBox.y = _y;
}
void Hero::flip(SDL_RendererFlip &_flipType)
{
	if (direction==1)
	{
		_flipType = SDL_FLIP_NONE;
	}
	if (direction==-1)
	{
		_flipType = SDL_FLIP_HORIZONTAL;
	}
}

