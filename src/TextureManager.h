#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class TextureManager
{
public:
	static SDL_Texture * loadTexture(std::string fileName, SDL_Renderer* renderer);
	static TTF_Font * loadFont(std::string fileName, const int& fontSize);
	static Mix_Chunk * loadSound(std::string fileName);
	static Mix_Music * loadMusic(std::string fileName);
};

#endif // !__TEXTURE_MANAGER_H__
