#include "Hero.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Texture.h"
#include"coins.h"
#include "Button.h"
#include"Cloud.h"
#include"Definition.h"
#include"Castle.h"

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Filan's Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
void Castle::render(SDL_Rect& camera)
{
	gCastleTexture.render(mBox.x - camera.x, mBox.y - camera.y);
}
void coinCollide(std::vector<Coin>&_coin, SDL_Rect& _box,int &_point)
{
	for (auto itr = _coin.begin(); itr != _coin.end(); )
	{
		if (checkCollision((*itr).getBox(), _box) == true)
		{
			itr = _coin.erase(itr);
			Mix_PlayChannel(-1, gCoin, 0);
			_point += 1;
		}
		else
			itr++;
	}
}
bool enemyCollide(std::vector<Enemy>&_enemy, Hero _hero)
{
	for (auto itr = _enemy.begin(); itr != _enemy.end();)
	{
		
		if (checkCollision((*itr).getBox(), _hero.getBox()) == true)
		{
			if (_hero.jump() == false) 
			
			{
				return true;
			}
			else 
			{
				itr = _enemy.erase(itr);
				
			}
		}
		else
			itr++;
	}
}
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//The level tiles
		Tile* tileSet[TOTAL_TILES];

		//Load media
		if (!loadMedia(tileSet))
		{
			printf("Failed to load media!\n");
		}
		else
		{	
			restart:
			SDL_Color textColor = { 0, 0, 0, 255 };
			Mix_PlayMusic(gMusic, -1);
			//Main loop flag
			bool quit = false;
			int frame = 0;
			int coinFrame = 0;
			bool menu = false;
			bool control = false;
			bool loose = false;
			bool res = false;
			int f = 0;
			//Event handler
			SDL_Event e;
			Hero hero;
			SDL_RendererFlip flipType = SDL_FLIP_NONE;
			SDL_RendererFlip flipEnemyType[2];
			flipEnemyType[0] = SDL_FLIP_NONE;
			flipEnemyType[1] = SDL_FLIP_NONE;
			Uint32 startTime = 0;
			int point = 0;
			std::stringstream timeText;
			std::stringstream pointText;
			std::vector<Coin>coin;
			for (int i = 0; i < 30; i++)
			{
				Coin tmp;
				tmp.setBox(100 * i, 280);
				coin.push_back(tmp);
			}
			std::vector<Cloud>cloud;
			for (int i = 0; i < 30; i++)
			{
				Cloud tmp2;
				tmp2.setBox(300 * i, 50);
				cloud.push_back(tmp2);
			}

			std::vector<Enemy>enemy;
			for (int i = 0; i < 2; i++)
			{
				Enemy tmp1;
				if (i == 0)
					tmp1.setBox(940, 320);
				else if (i == 1)
					tmp1.setBox(1080, 320);
				enemy.push_back(tmp1);
			}
			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			//While application is running
			Castle castle;
			castle.setBox(7500, 60);
			while (!quit)
			{
				SDL_Rect* currentClip = &gHeroClips[frame / 6];
				SDL_Rect* currentCoinClip = &gCoinClips[coinFrame /61];

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						menu = false;
						control = false;
					}
					
					hero.handleEvent(e);
					//Handle button events
					
						gButtons[0].handleEvent(&e,menu);
						gButtons[1].handleEvent(&e,control);
						gButtons[2].handleEvent(&e,res);
					
				}
				
				hero.move(tileSet);
				hero.setCamera(camera);
				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				if (menu == false)
				{
					gTexture.render(0,0);
					gPlayTexture.render(20, 240);
					gControlTexture.render(20, 276);
					for (int i = 0; i < 2; ++i)
					{
						gButtons[i].render();
					}
				}
				if (control==true)
					gControl.render(0, 0);
				if (menu == true)
				{
					
					hero.flip(flipType);
					f++;
					if (f == 1) startTime = SDL_GetTicks();
					else f = 2;
					//Render level
					for (int i = 0; i < TOTAL_TILES; ++i)
					{
						tileSet[i]->render(camera);
					}
					for (int i = 0; i < enemy.size(); ++i)
					{
						enemy[i].move(tileSet);
						enemy[i].render(camera, flipEnemyType[i]);
						enemy[i].flip(flipEnemyType[i]);
					}

					timeText.str("");
					double time = (SDL_GetTicks() - startTime) / 1000;
					timeText << "time: " << time << "  s";
					pointText.str("");
					pointText << "point: " << point;
					if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
					{
						printf("Unable to render time texture!\n");
					}
					gTimeTextTexture.render(600, 20);
					if (!gPointTextTexture.loadFromRenderedText(pointText.str().c_str(), textColor))
					{
						printf("Unable to render time texture!\n");
					}
					gPointTextTexture.render(100, 20);

					castle.render(camera);
					hero.render(camera, currentClip, flipType);
					for (auto itr = coin.begin(); itr != coin.end(); itr++)
					{
						(*itr).render(camera, currentCoinClip);
						(*itr).animation(coinFrame, COIN_ANIMATION_FRAMES);
					}
					coinCollide(coin, hero.getBox(), point);
			
					for (auto itr = cloud.begin(); itr != cloud.end(); itr++)
					{
						(*itr).render(camera);
					}
					if (enemyCollide(enemy, hero) == true)
					{
						loose = true;
					}
					
					if (hero.getBox().y >= 384)
					{
						loose = true;
					}
				}
				std::cout << hero.getBox().y << std::endl;
				if (loose == true)
				{
					gTexture.render(0, 0);
					gLostTexture.render(400, 240);
					gAgainTexture.render(400, 276);
					gButtons[2].render();
					if (res == true)
					{
						goto restart;
					}
				}
				SDL_RenderPresent(gRenderer);
				hero.animation(frame, WALKING_ANIMATION_FRAMES);
			}
		}
		close(tileSet);
	}
	return 0;
}