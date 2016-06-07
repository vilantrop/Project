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
LButton gButtons[TOTAL_BUTTONS];
LTexture gButtonSpriteSheetTexture;
LTexture gControl;