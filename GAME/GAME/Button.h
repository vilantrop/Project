#pragma once
#include"func.h"

const int BUTTON_WIDTH=250;
const int BUTTON_HEIGHT=26;
const int TOTAL_BUTTONS =3;
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e,bool &_but);
	void setSize(int w, int h);
	//Shows button sprite
	void render();
	SDL_Point GetPosition();
	
private:
	//Top left position
	SDL_Point mPosition;
};
LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
	
}
SDL_Point LButton::GetPosition()
{
	return mPosition;
}
void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}
void LButton::setSize(int w, int h)
{
	int BUTTON_WIDTH = w;
	int BUTTON_HEIGHT = h;
}
void LButton::handleEvent(SDL_Event* e,bool &_but)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}
		//std::cout <<x << "::" << y << std::endl;
		if (inside==true)
		{
			switch (e->type)
			{


			case SDL_MOUSEBUTTONDOWN:
			{
				_but = true; break;
			}
			}
		}
	}
}



