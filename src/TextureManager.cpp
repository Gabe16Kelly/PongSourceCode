#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(std::string fileName, SDL_Renderer* renderer) {

	SDL_Surface* tempSurf = IMG_Load(fileName.c_str());

	if (tempSurf != nullptr)
	{
		std::cout << "loaded image named: " << fileName.c_str() << std::endl;
	}
	else {
		std::cout << "could not load image named: " << fileName.c_str() << std::endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurf);

	SDL_FreeSurface(tempSurf);

	return texture;
}

TTF_Font* TextureManager::loadFont(std::string fileName, const int& pt) {

	TTF_Font* font = TTF_OpenFont(fileName.c_str(), pt);

	if (font != nullptr) {
		std::cout << "loaded font named: " << fileName.c_str() << std::endl;
	}
	else {
		std::cout << "could not load font named: " << fileName.c_str() << std::endl;
	}

	return font;
}

Mix_Chunk* TextureManager::loadSound(std::string fileName) {

	Mix_Chunk* sound = Mix_LoadWAV(fileName.c_str());

	if (sound != nullptr) {
		std::cout << "loaded sound named: " << fileName.c_str() << std::endl;
	}
	else {
		std::cout << "did not load sound named: " << fileName.c_str()  << std::endl;
	}

	return sound;
}

Mix_Music* TextureManager::loadMusic(std::string fileName){

	Mix_Music* music = Mix_LoadMUS(fileName.c_str());

	if (music != nullptr) {
		std::cout << "loaded music named: " << fileName.c_str() << std::endl;
	}
	else {
		std::cout << "did not load music named: " << fileName.c_str() << std::endl;
	}

	Mix_VolumeMusic(80);

	return music;
}








