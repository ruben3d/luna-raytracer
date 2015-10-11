/*
   Copyright 2015 Ruben Moreno Montoliu <ruben3d at gmail dot com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

//
// Display.cpp - Created on 2008.12.05
//

#include "Display.h"
#include "SDL/SDL.h"

struct DisplayStruct
{
	unsigned int width, height;
	SDL_Surface *surface;
	unsigned int *backbuffer;
};

Display::Display(const unsigned int width, const unsigned int height)
	: display(NULL)
{
	display = new DisplayStruct();
	display->width = width;
	display->height = height;

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("Error: SDL_Init(SDL_INIT_EVERYTHING) == -1\n");
		return;
	}

	display->surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

	if(display->surface == NULL)
	{
		printf("Error: display->surface == NULL\n");
		return;
	}

	SDL_WM_SetCaption("Raytracer", NULL);

	display->backbuffer = new unsigned int[width*height];
}

Display::~Display()
{
	delete[] display->backbuffer;
	SDL_Quit();
	delete display;
}

unsigned int *Display::getBackBuffer()
{
	return display->backbuffer;
}

void Display::swapBuffers()
{
	if (SDL_MUSTLOCK(display->surface))
	{
		SDL_LockSurface(display->surface);
	}

	int total = display->width * display->height;
	memcpy(display->surface->pixels, display->backbuffer,
			total*sizeof(unsigned int));
	/*
	for (int i=0; i<total; i++)
	{
		((unsigned int*)display->surface->pixels)[i] = display->backbuffer[i];
	}*/

	if (SDL_MUSTLOCK(display->surface))
	{
		SDL_UnlockSurface(display->surface);
	}

	if(SDL_Flip(display->surface) == -1)
	{
		printf("Error: SDL_Flip( screen ) == -1\n");
		return;
	}
}

void Display::swapBuffers(const unsigned int x0, const unsigned int y0, const unsigned int x1, const unsigned int y1)
{
	if (SDL_MUSTLOCK(display->surface))
	{
		SDL_LockSurface(display->surface);
	}

	unsigned int width = (x1-x0+1)*sizeof(unsigned int);
	for (unsigned int y=y0; y<=y1; y++)
	{
		unsigned int pos = x0+y*display->width;
		memcpy(&((unsigned int*)display->surface->pixels)[pos], &(display->backbuffer[pos]), width);
	}

	if (SDL_MUSTLOCK(display->surface))
	{
		SDL_UnlockSurface(display->surface);
	}

	if(SDL_Flip(display->surface) == -1)
	{
		printf("Error: SDL_Flip( screen ) == -1\n");
		return;
	}
}
