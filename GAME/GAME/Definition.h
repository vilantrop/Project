#pragma once
#include "func.h"


const int WALKING_ANIMATION_FRAMES = 6;
const int COIN_ANIMATION_FRAMES = 61;
LTexture gTexture;
LTexture gHeroTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
LTexture gEnemyTexture; 
LTexture gHeroSheetTexture;
LTexture gCoinSheetTexture;
SDL_Rect gHeroClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gCoinClips[COIN_ANIMATION_FRAMES];
TTF_Font *gFont = NULL;
LTexture gTimeTextTexture;
LTexture gPointTextTexture;
LTexture gPlayTexture;
LTexture gControlTexture;
LTexture gCloudTexture;
LTexture gLostTexture;
LTexture gAgainTexture;
LTexture gCastleTexture;
LButton gButtons[TOTAL_BUTTONS];
LTexture gButtonSpriteSheetTexture;
LTexture gControl;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void coinTexture()
{
	int pos = 0;
	for (int i = 0; i < 61; i++)
	{
		gCoinClips[i].x = pos;
		gCoinClips[i].y = 0;
		gCoinClips[i].w = 24;
		gCoinClips[i].h = 24;
		pos += 24;

	}
}
bool setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("lazy.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[TILE_FLOOR].x = 0;
			gTileClips[TILE_FLOOR].y = 0;
			gTileClips[TILE_FLOOR].w = TILE_WIDTH;
			gTileClips[TILE_FLOOR].h = TILE_HEIGHT;

			gTileClips[TILE_SKY].x = 42;
			gTileClips[TILE_SKY].y = 0;
			gTileClips[TILE_SKY].w = TILE_WIDTH;
			gTileClips[TILE_SKY].h = TILE_HEIGHT;

			gTileClips[TILE_BRICK].x = 82;
			gTileClips[TILE_BRICK].y = 0;
			gTileClips[TILE_BRICK].w = TILE_WIDTH;
			gTileClips[TILE_BRICK].h = TILE_HEIGHT;


		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}
bool loadMedia(Tile* tiles[])
{
	//Loading success flag
	bool success = true;
	if (!gTexture.loadFromFile("intro.png"))
	{
		printf("Failed to load tex texture!\n");
		success = false;
	}

	if (!gControl.loadFromFile("11.png"))
	{
		printf("Failed to load tex texture!\n");
		success = false;
	}

	if (!gHeroSheetTexture.loadFromFile("hero_spritesheet.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	if (!gCastleTexture.loadFromFile("smallcastle.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		////Set sprite clips
		gHeroClips[0].x = 10;
		gHeroClips[0].y = 114;
		gHeroClips[0].w = 67;
		gHeroClips[0].h = 66;

		gHeroClips[1].x = 92;
		gHeroClips[1].y = 114;
		gHeroClips[1].w = 67;
		gHeroClips[1].h = 66;

		gHeroClips[2].x = 177;
		gHeroClips[2].y = 114;
		gHeroClips[2].w = 67;
		gHeroClips[2].h = 66;

		gHeroClips[3].x = 262;
		gHeroClips[3].y = 114;
		gHeroClips[3].w = 67;
		gHeroClips[3].h = 66;

		gHeroClips[4].x = 341;
		gHeroClips[4].y = 114;
		gHeroClips[4].w = 67;
		gHeroClips[4].h = 66;

		gHeroClips[5].x = 418;
		gHeroClips[5].y = 114;
		gHeroClips[5].w = 67;
		gHeroClips[5].h = 66;


	}
	if (!gCoinSheetTexture.loadFromFile("coin24.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		coinTexture();

	}
	gFont = TTF_OpenFont("GB.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gPlayTexture.loadFromRenderedText("PLAY", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gControlTexture.loadFromRenderedText("Control Instruction", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gLostTexture.loadFromRenderedText("GAME OVER", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gAgainTexture.loadFromRenderedText("Main Menu", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}


	}

	gCoin = Mix_LoadWAV("mario_coin.mp3");
	if (gCoin == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	if (!gEnemyTexture.loadFromFile("alladyn.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if (!gCloudTexture.loadFromFile("cloud.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	gMusic = Mix_LoadMUS("rush.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	//Load tile texture
	if (!gTileTexture.loadFromFile("ntiles.png"))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}
void close(Tile* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i] == NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}
	gLostTexture.free();
	gTexture.free();
	gTimeTextTexture.free();
	gHeroTexture.free();
	gTileTexture.free();
	gEnemyTexture.free();
	gHeroSheetTexture.free();
	gCoinSheetTexture.free();
	Mix_FreeChunk(gCoin);
	gCoin = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
void Tile::render(SDL_Rect& camera)
{
	if (checkCollision(camera, mBox))
	{
		//Show the tile
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
	}
}
void Hero::render(SDL_Rect& camera, SDL_Rect* currentClip, SDL_RendererFlip &_flipType)
{
	gHeroSheetTexture.render(mBox.x - camera.x, mBox.y - camera.y, currentClip,NULL,NULL,_flipType);
}
void Coin::render(SDL_Rect& camera, SDL_Rect* currentClip)
{
	gCoinSheetTexture.render(mBox.x - camera.x, mBox.y - camera.y, currentClip);
}
void Enemy::render(SDL_Rect& camera , SDL_RendererFlip &_flipType)
{
	
	gEnemyTexture.render(mBox.x - camera.x, mBox.y - camera.y , NULL, NULL, NULL, _flipType);
}
void Cloud::render(SDL_Rect& camera)
{
	gCloudTexture.render(mBox.x - camera.x, mBox.y - camera.y);
}
void LButton::render()
{
	gButtons[0].setPosition(20, 240);
	gButtons[1].setPosition(20, 276);
	gButtons[2].setPosition(400, 276);
}